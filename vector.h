#include <memory>
#include <algorithm>

//using std::allocator;
template <class T>
class allocator
{
public:
    T *allocate(size_t n) // išskirti `raw` atmintį
    {
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }            
    void deallocate(T *p, size_t n)   // atlaisvinti atmintį
    {
        ::operator delete(p, n * sizeof(T));
    }
    void construct(T *p, const T &val) // sukonstruoti 1 objektą
    {
        new (p) T(val);
    }
    void destroy(T *p)              // sunaikinti 1 objektą
    {
        p->~T();
    }
};

template <class T, class... Args>
class vector
{
public: 
// member types
    typedef T value_type;
    //typedef typename allocator_type;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    // typedef typename std::allocator_traits<allocator_type>::pointer pointer;
    // typedef typename std::allocator_traits<allocator>::const_pointer const_pointer;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

// member functions

    //constructors
    
    vector() { create(); }
    explicit vector(size_type n, const T &t = T{}) { create(n, t); }
    vector(const vector &v) { create(v.begin(), v.end()); }
    vector(iterator a, iterator b) { create(a, b); }

    //destructor
    ~vector() { uncreate(); } 

    // operator =
    vector &operator=(const vector &source)
    {
        // patikriname ar ne lygu
        if (&source != this)
        {
            // atlaisviname seną this objekto atmintį
            uncreate();
            // perkopijuojame elementus iš source į this
            create(source.begin(), source.end());
        }
        return *this;
    }

    //assign
    void assign(size_type n, const T &t) { create(n, t); }
    void assign(const_iterator first, const_iterator last) { create(first, last); }

    // element access
    T &at(size_type n) { return (n < size()) ? data[n] : throw std::out_of_range("vector::at()"); }

    T &operator[](size_type n) { return data[n]; }
    const T &operator[](size_type i) const { return data[i]; }

    T &front() { return data[0]; }
    const T &front() const { return data[0]; }

    T &back() { return data[size() - 1]; }
    const T &back() const { return data[size() - 1]; }


    // iterators
    iterator begin() noexcept { return data; }
    const_iterator begin() const noexcept { return data; }
    const_iterator cbegin() const noexcept { return data; }

    iterator end() noexcept { return avail; }
    const_iterator end() const noexcept { return avail; }
    const_iterator cend() const noexcept { return avail; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(avail); }
    const_reverse_iterator rbegin() const noexcept { return reverse_iterator(avail); }
    const_reverse_iterator crbegin() const noexcept { return reverse_iterator(avail); }

    reverse_iterator rend() noexcept { return reverse_iterator(data); }
    const_reverse_iterator rend() const noexcept { return reverse_iterator(data); }
    const_reverse_iterator crend() const noexcept { return reverse_iterator(data); }

    // capacity
    bool empty() const noexcept { return data == avail; }
    size_type size() const noexcept { return avail - data; }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }
    void reserve(size_type n) { if (n > capacity()) grow(n); }
    size_type capacity() const noexcept { return limit - data; }
    void shrink_to_fit() { limit = avail; }

    // modifiers
    void clear() { uncreate(); }
    iterator insert(const_iterator position, const T &t)
    {
        // patikriname ar yra vietos naujam elementui
        if (avail == limit)
            grow();
        // perkopijuojame elementus į dešinę
        iterator pos = const_cast<iterator>(position);
        std::copy_backward(pos, avail, avail + 1);
        // įterpiame naują elementą į position vietą
        *pos = t;
        // padidiname avail
        avail++;
        return pos;
    }

    template <typename... Args2>
    constexpr iterator emplace(const_iterator pos, Args2 &&...args)
    {
        if (avail == limit)
            grow();
        iterator position = const_cast<iterator>(pos);
        std::copy_backward(position, avail, avail + 1);
        *position = T(std::forward<Args2>(args)...);
        avail++;
        return position;
    }

    template <typename... Args2>
    iterator erase(const_iterator position)
    {
        iterator pos = const_cast<iterator>(position);
        std::copy(pos + 1, avail, pos);
        alloc.destroy(--avail);
        return pos;
    }

    void push_back(const T &t)
    {
        if (avail == limit)
            grow();
        unchecked_append(t);
    }

    template <typename... Args2>
    void emplace_back(Args2 &&...args)
    {
        T item(args...);
        push_back(item);
    }

    void pop_back()
    {
        if (avail == data)
            throw std::out_of_range("vector::pop_back()");
        avail--;
        alloc.destroy(avail);
    }

    void resize(size_type n, const T &t = T{})
    {
        if (n > size())
        {
            if (n > capacity())
                grow(n);
            for (size_type i = size(); i != n; i++)
                alloc.construct(avail++, t);
        }
        else if (n < size())
        {
            while (avail != data + n)
                alloc.destroy(--avail);
        }
    }

    void swap(vector &v)
    {
        std::swap(data, v.data);
        std::swap(avail, v.avail);
        std::swap(limit, v.limit);
    }

private:
    iterator data;  // pakeista iš T* į iterator
    iterator avail; // pirmasis po paskutiniojo sukonstruoto vector elementas
    iterator limit; // pakeista iš T* į iterator

    // atminties išskyrimo valdymui
    allocator<T> alloc;
    // išskirti atmintį (array) ir ją inicializuoti
    void create() { data = avail = limit = nullptr; }
    void create(size_type n, const T &val)
    {
        data = alloc.allocate(n);                  // grąžina ptr į array pirmą elementą
        limit = avail = data + n;                  // sustato rodykles į vietas
        std::uninitialized_fill(data, limit, val); // inicializuoja elementus val reikšme
    }
    void create(const_iterator i, const_iterator j)
    {
        data = alloc.allocate(j - i);                        // išskirti vietos j-i elementams
        limit = avail = std::uninitialized_copy(i, j, data); // nukopijuoja elementus iš intervalo
    }
    // sunaikinti elementus array ir atlaisvinti atmintį
    void uncreate()
    {
        if (data)
        {
            // sunaikinti (atbuline tvarka) sukonstruotus elementus
            iterator it = avail;
            while (it != data)
                alloc.destroy(--it);
            // atlaisvinti išskirtą atmintį. Turi būti data != nullptr
            alloc.deallocate(data, limit - data);
        }
        // reset'inam pointer'iuss - vector'ius tuščias
        data = limit = avail = nullptr;
    }
    // pagalbinės funkcijos push_back realizacijai
    void grow()
    {
        // dvigubai daugiau vietos, nei buvo
        size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
        // išskirti naują vietą ir perkopijuoti egzistuojančius elementus
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data, avail, new_data);
        // atlaisvinti seną vietą
        uncreate();
        // reset'int rodykles į naujai išskirtą vietą
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }
    void grow(int n)
    {
        size_type new_size = n;
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data, avail, new_data);
        // atlaisvinti seną vietą
        uncreate();
        // reset'int rodykles į naujai išskirtą vietą
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }
    void unchecked_append(const T &val) { alloc.construct(avail++, val); }
};