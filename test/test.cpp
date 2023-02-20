#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include "../BigInteger/big_integer.h"

TEST_CASE("Class Big integer", "[big_integer]")
{
    SECTION("Inicialize and constructor")
    {
        std::wstring str(L"111");
        auto number1 = big_integer(str);
        auto number2 = big_integer(L"-222");

        CHECK(number1.getNum() == L"111");
        CHECK(str == L"");
        CHECK(str.size() == 0);
        CHECK(number2.getNum() == L"-222");
        
        auto number3(number1);
        CHECK(number3.getNum() == L"111");

        number3 = number2;
        CHECK(number2.getNum() == L"-222");
        CHECK(number3.getNum() == L"-222");

        try
        {
            number3 = big_integer(L"23b");
        }
        catch (std::exception){}
        try
        {
            number3 = big_integer(L"c111");
        }
        catch (std::exception) {}
        try
        {
            number3 = big_integer(L"111 111");
        }
        catch (std::exception) {}
        try
        {
            number3 = big_integer(L"111.111");
        }
        catch (std::exception) {}

        number3 = big_integer(L"");
        CHECK(number3.getNum() == L"0");
    }
    SECTION("Compare big integer")
    {
        auto number1(big_integer(L"11111"));
        auto number2(big_integer(L"11111"));

        CHECK((number1 == number2) == true);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == false);

        number1 = (big_integer(L"21111"));
        number2 = (big_integer(L"11111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);

        number1 = (big_integer(L"11112"));
        number2 = (big_integer(L"11111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);
        
        number1 = (big_integer(L"111111"));
        number2 = (big_integer(L"11111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);

        number1 = (big_integer(L"11111"));
        number2 = (big_integer(L"21111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);

        number1 = (big_integer(L"11111"));
        number2 = (big_integer(L"11112"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);

        number1 = (big_integer(L"11111"));
        number2 = (big_integer(L"111111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);

        number1 = (big_integer(L"-1"));
        number2 = (big_integer(L"-2"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);

        number1 = (big_integer(L"-10"));
        number2 = (big_integer(L"10"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);
    }
    SECTION("Operators +")
    {
        auto number1(big_integer(L"111"));
        auto number2(big_integer(L"111"));
        CHECK((number1 += number2).getNum() == L"222");
        CHECK((number1 + number2).getNum() == L"333");

        number1 = (big_integer(L"999"));
        number2 = (big_integer(L"111"));
        CHECK((number1 += number2).getNum() == L"1110");
        CHECK((number1 + number2).getNum() == L"1221");

        number1 = (big_integer(L"000000111"));
        number2 = (big_integer(L"100111"));
        CHECK((number1 += number2).getNum() == L"100222");
        CHECK((number1 + number2).getNum() == L"200333");

        number1 = (big_integer(L"100111"));
        number2 = (big_integer(L"000000111"));
        CHECK((number1 += number2).getNum() == L"100222");
        CHECK((number1 + number2).getNum() == L"100333");

        number1 = (big_integer(L"9999999999"));
        number2 = (big_integer(L"100000"));
        CHECK((number1 += number2).getNum() == L"10000099999");
        CHECK((number1 + number2).getNum() == L"10000199999");

        number1 = (big_integer(L"100000"));
        number2 = (big_integer(L"9999999999"));
        CHECK((number1 += number2).getNum() == L"10000099999");
        CHECK((number1 + number2).getNum() == L"20000099998");

        number1 = (big_integer(L"2"));
        number2 = (big_integer(L"3"));
        CHECK((number1 + number2).getNum() == L"5");
        CHECK((number1 += number2).getNum() == L"5");

        number1 = (big_integer(L"-247"));
        number2 = (big_integer(L"308"));
        CHECK((number1 + number2).getNum() == L"61");
        CHECK((number1 += number2).getNum() == L"61");

        number1 = (big_integer(L"221"));
        number2 = (big_integer(L"-399"));
        CHECK((number1 + number2).getNum() == L"-178");
        CHECK((number1 += number2).getNum() == L"-178");

        number1 = (big_integer(L"-283"));
        number2 = (big_integer(L"-309"));
        CHECK((number1 + number2).getNum() == L"-592");
        CHECK((number1 += number2).getNum() == L"-592");

        number1 = (big_integer(L"-326"));
        number2 = (big_integer(L"-290"));
        CHECK((number1 + number2).getNum() == L"-616");
        CHECK((number1 += number2).getNum() == L"-616");
    }
    SECTION("Operators -")
    {
        auto number1(big_integer(L"111"));
        auto number2(big_integer(L"111"));
        CHECK((number1 -= number2).getNum() == L"0");
        CHECK((number1 - number2).getNum() == L"-111");

        number1 = (big_integer(L"999"));
        number2 = (big_integer(L"111"));
        CHECK((number1 -= number2).getNum() == L"888");
        CHECK((number1 - number2).getNum() == L"777");

        number1 = (big_integer(L"000000111"));
        number2 = (big_integer(L"100111"));
        CHECK((number1 -= number2).getNum() == L"-100000");
        CHECK((number1 - number2).getNum() == L"-200111");

        number1 = (big_integer(L"100111"));
        number2 = (big_integer(L"000000111"));
        CHECK((number1 -= number2).getNum() == L"100000");
        CHECK((number1 - number2).getNum() == L"99889");

        number1 = (big_integer(L"9999999999"));
        number2 = (big_integer(L"100000"));
        CHECK((number1 -= number2).getNum() == L"9999899999");
        CHECK((number1 - number2).getNum() == L"9999799999");

        number1 = (big_integer(L"100000"));
        number2 = (big_integer(L"9999999999"));
        CHECK((number1 -= number2).getNum() == L"-9999899999");
        CHECK((number1 - number2).getNum() == L"-19999899998");

        number1 = (big_integer(L"2"));
        number2 = (big_integer(L"-3"));
        CHECK((number1 - number2).getNum() == L"5");
        CHECK((number1 -= number2).getNum() == L"5");

        number1 = (big_integer(L"-2"));
        number2 = (big_integer(L"3"));
        CHECK((number1 - number2).getNum() == L"-5");
        CHECK((number1 -= number2).getNum() == L"-5");
        
        number1 = (big_integer(L"-2"));
        number2 = (big_integer(L"-3"));
        CHECK((number1 - number2).getNum() == L"1");
        CHECK((number1 -= number2).getNum() == L"1");

        number1 = (big_integer(L"-203"));
        number2 = (big_integer(L"-315"));
        CHECK((number1 - number2).getNum() == L"112");
        CHECK((number1 -= number2).getNum() == L"112");

        number1 = (big_integer(L"-346"));
        number2 = (big_integer(L"-230"));
        CHECK((number1 - number2).getNum() == L"-116");
        CHECK((number1 -= number2).getNum() == L"-116");
    }
    SECTION("Operators *")
    {
        auto number1(big_integer(L"111"));
        auto number2(big_integer(L"111"));
        CHECK((number1 * number2).getNum() == L"12321");
        CHECK((number1 *= number2).getNum() == L"12321");
        
        number1 = (big_integer(L"999"));
        number2 = (big_integer(L"111"));
        CHECK((number1 * number2).getNum() == L"110889");
        CHECK((number1 *= number2).getNum() == L"110889");

        number1 = (big_integer(L"9"));
        number2 = (big_integer(L"999"));
        CHECK((number1 * number2).getNum() == L"8991");
        CHECK((number1 *= number2).getNum() == L"8991");

        number1 = (big_integer(L"123456789"));
        number2 = (big_integer(L"999"));
        CHECK((number1 * number2).getNum() == L"123333332211");
        CHECK((number1 *= number2).getNum() == L"123333332211");

        number1 = (big_integer(L"45632"));
        number2 = (big_integer(L"9999998888877777666666"));
        CHECK((number1 * number2).getNum() == L"456319949297270750485302912");
        CHECK((number1 *= number2).getNum() == L"456319949297270750485302912");

        number1 = (big_integer(L"25"));
        number2 = (big_integer(L"-5"));
        CHECK((number1 * number2).getNum() == L"-125");
        CHECK((number1 *= number2).getNum() == L"-125");

        number1 = (big_integer(L"-5"));
        number2 = (big_integer(L"25"));
        CHECK((number1 * number2).getNum() == L"-125");
        CHECK((number1 *= number2).getNum() == L"-125");

        number1 = (big_integer(L"-3"));
        number2 = (big_integer(L"-30"));
        CHECK((number1 * number2).getNum() == L"90");
        CHECK((number1 *= number2).getNum() == L"90");
    }
    SECTION("Operators /")
    {
        auto number1(big_integer(L"12345"));
        auto number2(big_integer(L"12345"));
        CHECK((number1 / number2).getNum() == L"1");

        number1 = (big_integer(L"111"));
        number2 = (big_integer(L"911"));
        CHECK((number1 / number2).getNum() == L"0");
    }
}

int main()
{
    return Catch::Session().run();
}
