Naudojimo instrukcija: Atidaryti terminalą programos aplanke, įvesti make, spaust enter ir sekti instrukcijas terminale

# v1.0

Dalinimas 1 strategija (pernaudojant pradinį konteinerį):

1. Naudojant find_if surikiuotame studentų konteineryje rasti, kur vidurkis>=5, vieta pasižymima iteratoriumi it
2. Sukuriamas naujas konteineris, kurį inicializuojant jam priskiriamos reikšmės iš pirminio studentų konteinerio nuo iteratoriaus iki pabaigos
3. Pirminis studentų konteineris naudojant resize funkciją sumažinamas, taip panaikinant naująjame konteineryje esančias reikšmes

Dalinimas 2 strategija (sukuriant 2 naujus konteinerius):

1. Naudojant find_if surikiuotame studentų konteineryje rasti, kur vidurkis>=5, vieta pasižymima iteratoriumi it
2. Du nauji konteineriai, naudojant resize, padidinami, kad talpintų tiek elementų, kiek reikės (distance(it, pradinis_konteineris.end()); advance(it, -1); distance(pradinis_konteineris.begin(), it))
3. Naudojant funkciją copy, elementai kopijuojami į naujus konteinerius
4. pradinis konteineris panaikinamas

Dalinimas 3 strategija (pernaudojant pradinį konteinerį, priskiriant reikšmes naujam) (tik su list):

1. Naudojant find_if surikiuotame studentų konteineryje rasti, kur vidurkis>=5, vieta pasižymima iteratoriumi it
2. Naudojant splice funkciją, pradinio konteinerio dalis priskiriama naujam konteineriui

| **Vector**   | Dalinimas truko: | RAM apkrova |
| ------------ | ---------------- | ----------- |
| 1 strategija | 0.1995s          | 809MB       |
| 2 startegija | 0.5371s          | 1.05GB      |

| **Deque**    | Dalinimas truko: | RAM apkrova |
| ------------ | ---------------- | ----------- |
| 1 strategija | 0.2264s          | 667MB       |
| 2 startegija | 0.4863s          | 743MB       |

| **List**     | Dalinimas truko: | RAM apkrova |
| ------------ | ---------------- | ----------- |
| 1 strategija | 3.0062s          | 1.13GB      |
| 2 startegija | 5.4736s          | 1.50GB      |
| 3 startegija | 1.2828s          | 769MB       |

# v0.5

Greitaveika

| **Vector**       | **1k**    | **10k**  | **100k** | **1M** | **10M** |
| ---------------- | --------- | -------- | -------- | ------ | ------- |
| **Nuskaitymas**  | _0.00469_ | _0.0639_ | _0.355_  | _3.47_ | _34.2_  |
| **Rikiavimas 1** | _0.00008_ | _0.0007_ | _0.007_  | _0.08_ | _0.8_   |
| **Dalinimas**    | _0.00002_ | _0.0000_ | _0.001_  | _0.01_ | _0.2_   |
| **Rikiavimas 2** | _0.00024_ | _0.0034_ | _0.044_  | _0.51_ | _6.7_   |
| **Išvedimas**    | _0.00135_ | _0.0096_ | _0.095_  | _0.78_ | _8.6_   |
| **Viso**         | _0.00641_ | _0.0779_ | _0.503_  | _4.87_ | _50.7_  |

[Perdaryta vietoj vector naudojant deque](https://github.com/Zeromskas/Objektinis-programavimas/tree/v0.5-deque)

| **Deque**        | **1k**    | **10k**  | **100k** | **1M** | **10M** |
| ---------------- | --------- | -------- | -------- | ------ | ------- |
| **Nuskaitymas**  | _0.00479_ | _0.0381_ | _0.369_  | _3.52_ | _34.8_  |
| **Rikiavimas 1** | _0.00013_ | _0.0008_ | _0.008_  | _0.08_ | _1.3_   |
| **Dalinimas**    | _0.00003_ | _0.0002_ | _0.002_  | _0.02_ | _0.3_   |
| **Rikiavimas 2** | _0.00030_ | _0.0034_ | _0.047_  | _0.57_ | _6.6_   |
| **Išvedimas**    | _0.00148_ | _0.0093_ | _0.088_  | _0.81_ | _8.5_   |
| **Viso**         | _0.00673_ | _0.0518_ | _0.514_  | _5.00_ | _51.6_  |

[Perdaryta vietoj vector naudojant list](https://github.com/Zeromskas/Objektinis-programavimas/tree/v0.5-list)

| **List**         | **1k**    | **10k**  | **100k** | **1M** | **10M** |
| ---------------- | --------- | -------- | -------- | ------ | ------- |
| **Nuskaitymas**  | _0.00670_ | _0.0538_ | _0.493_  | _4.45_ | _44.1_  |
| **Rikiavimas 1** | _0.00009_ | _0.0011_ | _0.018_  | _0.48_ | _9.5_   |
| **Dalinimas**    | _0.00001_ | _0.0001_ | _0.004_  | _0.09_ | _1.3_   |
| **Rikiavimas 2** | _0.00034_ | _0.0032_ | _0.048_  | _0.96_ | _17.0_  |
| **Išvedimas**    | _0.00149_ | _0.0110_ | _0.097_  | _0.83_ | _9.1_   |
| **Viso**         | _0.00864_ | _0.0692_ | _0.661_  | _6.82_ | _81.0_  |

# v0.4

1. Pridėta studentų pažymių failus generuojanti programa.
2. Pridėtas bendras ir atskirų programos dalių vykdymo laiko skaičiavimas.
3. Patobulinta studentų sarašo rikiavimo funkcija (pridėta galimybė pasirinkti rikiuoti pagal vardus arba pagal galutinius įvertinimus).
4. Pridėta studento sarašo dalinimo į dvi dalis (Pass ir Fail) funkcija.
5. Rezultatas gaunamas kaip 2 atskiri failai ("studPass.txt", "studFail.txt").
6. Optimizuotas RAM naudojimas.

Programos veikimo principas:

1. Nuskaitomi studentų duomenys iš pasirinkto failo
2. Studentų sąrašas surikiuojamas pagal galutinius pažymius didėjimo tvarka
3. Sąrašas padalinamas į dvi dalis (<5 ir >=5)
4. Abi dalys surikiuojamos pagal vardą ir pavardę
5. Abi dalys išvedamos į atskirus failus

Atliktas programos [greitaveikos testavimas](https://github.com/Zeromskas/Objektinis-programavimas/blob/v0.4/greitaveikosAtaskaita.txt)

|                  | **1k**    | **10k**  | **100k** | **1M** | **10M** |
| ---------------- | --------- | -------- | -------- | ------ | ------- |
| **Nuskaitymas**  | _0.00919_ | _0.0440_ | _0.354_  | _3.37_ | _34.7_  |
| **Rikiavimas 1** | _0.00015_ | _0.0007_ | _0.007_  | _0.07_ | _0.8_   |
| **Dalinimas**    | _0.00003_ | _0.0002_ | _0.003_  | _0.03_ | _0.4_   |
| **Rikiavimas 2** | _0.00033_ | _0.0025_ | _0.033_  | _0.39_ | _4.6_   |
| **Išvedimas**    | _0.00231_ | _0.0100_ | _0.106_  | _0.79_ | _8.3_   |
| **Viso**         | _0.01219_ | _0.0579_ | _0.506_  | _4.68_ | _49.4_  |
|                  |           |          |          |        |         |
| **Generavimas**  | _0.00599_ | _0.0383_ | _0.381_  | _3.72_ | _35.2_  |

# v0.3

1. Struktūros perkeltos į header failą.
2. Pridėta galimybė pasirinkti duomenų failą iš aplankalo.
3. Naudojamas try-catch atidarinėjant failą.
4. Optimizuotas failo išvedimas, naudojant atskirą stream ir į rez.txt kreipiantis ir rašant duomenis kas dešimtą studentą.
5. Funkcijos perkeltos į atskirą failą "mylib.cpp"
6. Sukurtas MAKEFILE, leidžiantis paleisti programą į konsolę parašius "make"

# v0.2

1. Pridėta galimybė studentų pažymius skaityti iš failo "studentai.txt"
2. Patobulintas atsitiktinių duomenų generavimas naudojant "mt19937"
3. Patobulintas klaidingų įvedimų apdorojimas
4. Optimizuotas RAM naudojimas, apskaičiavus galutinius pažymius ištrinant nebereikalingus pažymius.
5. Duomenys išvedami į failą "rez.txt", bereikalingai neapkraunant konsolės

# v0.1

1.  Programa nuskaito vartotojo įvedamus duomenis: studento vardą ir pavardę.
2.  Leidžia įvesti pažymius ranka, arba generuoti atsitiktinius.
3.  Ranka vedamų pažymių kiekis neribojamas, atsitiktinai generuojant pazymius sugeneruojami 0-20 pažymių. Pažymiai privalo būti dešimtbalėje sistemoje (_0-10_)
4.  Vartotojas, įvedęs visus pažymius, įveda bet kokią raidę ir taip yra sustabdomas pažymių įvedimas.
5.  Duodama įvesti egzamino pažymį (_0-10_) (_privaloma_), prieš tai pasirinkus generavimą atsitiktinai, egzamino pažymys sugeneruojamas atsitiktinai.
6.  Pabaigus pildyti vieno studento pažymius, duodamas pasirinkimas pildyti dar vieno studento duomenis (t) arba baigti pildymą (n) (studentų kiekis neribojamas)
7.  Vartotojui duodamas pasirinkimas gauti 3 rūšių duomenis (_Galutinis balas pagal vidurkį - 1; galutinis balas pagal medianą - 2; studentų pažymius - 3_) arba ištrinti duomenis ir išeiti - _0_. Pasirinkti išvedimą leidžiama neribotą kiekį kartų.

Dvi versijos: 1. naudojant C masyvus 2. naudojant vektorius
