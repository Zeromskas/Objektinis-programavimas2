
#include "functions.h"
#include <gtest/gtest.h>

TEST(compareName, compareNames)
{
    vector<int> grades;
    Student a("Antanas", "Baumila", grades, 10);
    Student b("Jonas", "Baumila", grades, 10);

    EXPECT_EQ(compareName(a, b), 1) << "Wrong compare result";
}

TEST(generateRandom, generate10Students)
{
    vector<Student> students;
    generateRandom(students, {10, 10});

    ASSERT_EQ(students.size(), 10) <<"Wrong vector size";
    for(int i=0; i<students.size(); i++)
    {
        ASSERT_EQ(students[i].getName(), "Vardas"+to_string(i)) << "Wrong name";
        ASSERT_EQ(students[i].getSurname(), "Pavardė"+to_string(i)) << "Wrong surname";
        ASSERT_EQ(students[i].getAverage() >= 0 && students[i].getAverage() <= 10, true) << "Wrong average";
        ASSERT_EQ(students[i].getMedian() >= 0 && students[i].getMedian() <= 10, true) << "Wrong median";
    }
}

TEST(generateFile, generateFileAndReadIt)
{
    generateFile({100, 9});
    vector<Student> students;
    readFile(students, "studentai100.txt");
    EXPECT_EQ(students.size(), 100) << "Wrong vector size";
    for (int i = 0; i < students.size(); i++)
    {
        ASSERT_EQ(students[i].getName(), "Vardas" + to_string(i+1)) << "Wrong name";
        ASSERT_EQ(students[i].getSurname(), "Pavardė" + to_string(i+1)) << "Wrong surname";
        ASSERT_EQ(students[i].getAverage() >= 0 && students[i].getAverage() <= 10, true) << "Wrong average";
        ASSERT_EQ(students[i].getMedian() >= 0 && students[i].getMedian() <= 10, true) << "Wrong median";
    }
}





int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}