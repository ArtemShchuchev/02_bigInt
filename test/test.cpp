#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include "../BigInteger/big_integer.h"

TEST_CASE("Class Big integer", "[big_integer]")
{
    SECTION("Inicialize and constructor")
    {
        std::string str("111");
        auto number1 = big_integer(str);
        auto number2 = big_integer("-222");

        CHECK(number1.getNum() == "111");
        CHECK(str == "");
        CHECK(str.size() == 0);
        CHECK(number2.getNum() == "-222");
        
        auto number3(number1);
        CHECK(number3.getNum() == "111");

        number3 = number2;
        CHECK(number2.getNum() == "-222");
        CHECK(number3.getNum() == "-222");

        try
        {
            number3 = big_integer("23b");
        }
        catch (std::runtime_error){}
        try
        {
            number3 = big_integer("c111");
        }
        catch (std::runtime_error) {}
        try
        {
            number3 = big_integer("111 111");
        }
        catch (std::runtime_error) {}
        try
        {
            number3 = big_integer("111.111");
        }
        catch (std::runtime_error) {}

        number3 = big_integer("");
        CHECK(number3.getNum() == "0");
    }
    SECTION("Compare big integer")
    {
        auto number1(big_integer("11111"));
        auto number2(big_integer("11111"));

        CHECK((number1 == number2) == true);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == false);

        number1 = (big_integer("21111"));
        number2 = (big_integer("11111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);

        number1 = (big_integer("11112"));
        number2 = (big_integer("11111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);
        
        number1 = (big_integer("111111"));
        number2 = (big_integer("11111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);

        number1 = (big_integer("11111"));
        number2 = (big_integer("21111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);

        number1 = (big_integer("11111"));
        number2 = (big_integer("11112"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);

        number1 = (big_integer("11111"));
        number2 = (big_integer("111111"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);

        number1 = (big_integer("-1"));
        number2 = (big_integer("-2"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == false);
        CHECK((number1 >= number2) == true);
        CHECK((number1 < number2) == false);
        CHECK((number1 > number2) == true);

        number1 = (big_integer("-10"));
        number2 = (big_integer("10"));

        CHECK((number1 == number2) == false);
        CHECK((number1 <= number2) == true);
        CHECK((number1 >= number2) == false);
        CHECK((number1 < number2) == true);
        CHECK((number1 > number2) == false);
    }
    SECTION("Operators +")
    {
        auto number1(big_integer("111"));
        auto number2(big_integer("111"));
        CHECK((number1 += number2).getNum() == "222");
        CHECK((number1 + number2).getNum() == "333");

        number1 = (big_integer("999"));
        number2 = (big_integer("111"));
        CHECK((number1 += number2).getNum() == "1110");
        CHECK((number1 + number2).getNum() == "1221");

        number1 = (big_integer("000000111"));
        number2 = (big_integer("100111"));
        CHECK((number1 += number2).getNum() == "100222");
        CHECK((number1 + number2).getNum() == "200333");

        number1 = (big_integer("100111"));
        number2 = (big_integer("000000111"));
        CHECK((number1 += number2).getNum() == "100222");
        CHECK((number1 + number2).getNum() == "100333");

        number1 = (big_integer("9999999999"));
        number2 = (big_integer("100000"));
        CHECK((number1 += number2).getNum() == "10000099999");
        CHECK((number1 + number2).getNum() == "10000199999");

        number1 = (big_integer("100000"));
        number2 = (big_integer("9999999999"));
        CHECK((number1 += number2).getNum() == "10000099999");
        CHECK((number1 + number2).getNum() == "20000099998");

        number1 = (big_integer("2"));
        number2 = (big_integer("3"));
        CHECK((number1 + number2).getNum() == "5");
        CHECK((number1 += number2).getNum() == "5");

        number1 = (big_integer("-247"));
        number2 = (big_integer("308"));
        CHECK((number1 + number2).getNum() == "61");
        CHECK((number1 += number2).getNum() == "61");

        number1 = (big_integer("221"));
        number2 = (big_integer("-399"));
        CHECK((number1 + number2).getNum() == "-178");
        CHECK((number1 += number2).getNum() == "-178");

        number1 = (big_integer("-283"));
        number2 = (big_integer("-309"));
        CHECK((number1 + number2).getNum() == "-592");
        CHECK((number1 += number2).getNum() == "-592");

        number1 = (big_integer("-326"));
        number2 = (big_integer("-290"));
        CHECK((number1 + number2).getNum() == "-616");
        CHECK((number1 += number2).getNum() == "-616");
    }
    SECTION("Operators -")
    {
        auto number1(big_integer("111"));
        auto number2(big_integer("111"));
        CHECK((number1 -= number2).getNum() == "0");
        CHECK((number1 - number2).getNum() == "-111");

        number1 = (big_integer("999"));
        number2 = (big_integer("111"));
        CHECK((number1 -= number2).getNum() == "888");
        CHECK((number1 - number2).getNum() == "777");

        number1 = (big_integer("000000111"));
        number2 = (big_integer("100111"));
        CHECK((number1 -= number2).getNum() == "-100000");
        CHECK((number1 - number2).getNum() == "-200111");

        number1 = (big_integer("100111"));
        number2 = (big_integer("000000111"));
        CHECK((number1 -= number2).getNum() == "100000");
        CHECK((number1 - number2).getNum() == "99889");

        number1 = (big_integer("9999999999"));
        number2 = (big_integer("100000"));
        CHECK((number1 -= number2).getNum() == "9999899999");
        CHECK((number1 - number2).getNum() == "9999799999");

        number1 = (big_integer("100000"));
        number2 = (big_integer("9999999999"));
        CHECK((number1 -= number2).getNum() == "-9999899999");
        CHECK((number1 - number2).getNum() == "-19999899998");

        number1 = (big_integer("2"));
        number2 = (big_integer("-3"));
        CHECK((number1 - number2).getNum() == "5");
        CHECK((number1 -= number2).getNum() == "5");

        number1 = (big_integer("-2"));
        number2 = (big_integer("3"));
        CHECK((number1 - number2).getNum() == "-5");
        CHECK((number1 -= number2).getNum() == "-5");
        
        number1 = (big_integer("-2"));
        number2 = (big_integer("-3"));
        CHECK((number1 - number2).getNum() == "1");
        CHECK((number1 -= number2).getNum() == "1");

        number1 = (big_integer("-203"));
        number2 = (big_integer("-315"));
        CHECK((number1 - number2).getNum() == "112");
        CHECK((number1 -= number2).getNum() == "112");

        number1 = (big_integer("-346"));
        number2 = (big_integer("-230"));
        CHECK((number1 - number2).getNum() == "-116");
        CHECK((number1 -= number2).getNum() == "-116");
    }
    SECTION("Operators *")
    {
        auto number1(big_integer("111"));
        auto number2(big_integer("111"));
        CHECK((number1 * number2).getNum() == "12321");
        CHECK((number1 *= number2).getNum() == "12321");
        
        number1 = (big_integer("999"));
        number2 = (big_integer("111"));
        CHECK((number1 * number2).getNum() == "110889");
        CHECK((number1 *= number2).getNum() == "110889");

        number1 = (big_integer("9"));
        number2 = (big_integer("999"));
        CHECK((number1 * number2).getNum() == "8991");
        CHECK((number1 *= number2).getNum() == "8991");

        number1 = (big_integer("123456789"));
        number2 = (big_integer("999"));
        CHECK((number1 * number2).getNum() == "123333332211");
        CHECK((number1 *= number2).getNum() == "123333332211");

        number1 = (big_integer("45632"));
        number2 = (big_integer("9999998888877777666666"));
        CHECK((number1 * number2).getNum() == "456319949297270750485302912");
        CHECK((number1 *= number2).getNum() == "456319949297270750485302912");

        number1 = (big_integer("25"));
        number2 = (big_integer("-5"));
        CHECK((number1 * number2).getNum() == "-125");
        CHECK((number1 *= number2).getNum() == "-125");

        number1 = (big_integer("-5"));
        number2 = (big_integer("25"));
        CHECK((number1 * number2).getNum() == "-125");
        CHECK((number1 *= number2).getNum() == "-125");

        number1 = (big_integer("-3"));
        number2 = (big_integer("-30"));
        CHECK((number1 * number2).getNum() == "90");
        CHECK((number1 *= number2).getNum() == "90");
    }
    SECTION("Operators /")
    {
        auto number1(big_integer("12345"));
        auto number2(big_integer("12345"));
        CHECK((number1 / number2).getNum() == "1");

        number1 = (big_integer("111"));
        number2 = (big_integer("911"));
        CHECK((number1 / number2).getNum() == "0");
    }
}

int main()
{
    return Catch::Session().run();
}
