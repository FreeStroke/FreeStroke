#include "../includes/skeletondatatest.h"

#include "../../includes/gestures/data/rawjointstate.h"

SkeletonDataTest::SkeletonDataTest(std::string name) : CppUnit::TestCase(name) {}

void SkeletonDataTest::runTest()
{
    QString str = "3142818 0,0353414 0,7788092 2,759029 0,01870631 0,9530811 2,723356 0,16237 0,6593802 2,725062 0,2785284 0,6601428 2,420907 0,2350549 0,818594 2,240513 0,219177 0,8586934 2,213341 -0,113889 0,6695147 2,76427 -0,2442654 0,65802 2,521382 -0,1839373 0,8285964 2,331903 -0,1678066 0,892403 2,290094 0,09208803 0,2781652 2,696631 0,1497035 -0,2980802 2,750106 0,1864739 -0,6853157 2,719812 0,2268384 -0,7531589 2,656485 -0,03248885 0,276049 2,717505 -0,06889521 -0,2885228 2,800947 -0,121444 -0,651255 2,775143 -0,153944 -0,7362887 2,719548 0,02996856 0,3414426 2,714999 0,03738236 0,4083826 2,766017";
    SkeletonData * sk = SkeletonData::fromLine(str);
    SkeletonData * sk2 = SkeletonData::fromLine(str);

    CPPUNIT_ASSERT( 0 == sk->toString().compare(sk2->toString()) );
    delete sk;
    delete sk2;
}
