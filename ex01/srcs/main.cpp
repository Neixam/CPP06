#include <iostream>
#include "Data.hpp"

int main()
{
    {
        Data toto = { 5, 'c', NULL };
        uintptr_t coco = serialize(&toto);
        Data *lolo = deserialize(coco);
        std::cout << ((&toto == lolo) ? "equal" : "not equal") << std::endl;
    }
    return 0;
}