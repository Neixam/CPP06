#include <iostream>
#include <cstdlib>
#include "Base.hpp"
#include "C.hpp"
#include "A.hpp"
#include "B.hpp"

Base *generate()
{
    int gen = rand();

    if (gen % 3 == 0)
    {
        std::cout << "C object generated" << std::endl;
        return new C();
    }
    else if (gen % 2 == 1)
    {
        std::cout << "A object generated" << std::endl;
        return new A();
    }
    else
    {
        std::cout << "B object generated" << std::endl;
        return new B();
    }
}

void identify(Base *p)
{
    if (dynamic_cast<A*>(p))
    {
        std::cout << "It's a A object" << std::endl;
        return;
    }
    if (dynamic_cast<B*>(p))
    {
        std::cout << "It's a B object" << std::endl;
        return;
    }
    if (dynamic_cast<C*>(p))
    {
        std::cout << "It's a C object" << std::endl;
        return;
    }
    std::cout << "Doesn't exist object" << std::endl;
}

void identify(Base &p)
{
    try
    {
        A &a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "It's a A object" << std::endl;
    }
    catch (std::exception &e1)
    {
        try
        {
            B &b = dynamic_cast<B&>(p);
            (void)b;
            std::cout << "It's a B object" << std::endl;

        }
        catch (std::exception &e2)
        {
            try
            {
                C &c = dynamic_cast<C&>(p);
                (void)c;
                std::cout << "It's a C object" << std::endl;
            }
            catch (std::exception &e3)
            {
                std::cout << e1.what() << ": " << e2.what() << ": " << e3.what() << ": " << std::endl;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    {
        Base *coco = generate();

        identify(coco);
        identify(*coco);
        delete coco;
    }
    {
        Base *coco = generate();

        identify(coco);
        identify(*coco);
        delete coco;
    }
    {
        Base *coco = generate();

        identify(coco);
        identify(*coco);
        delete coco;
    }
    return 0;
}