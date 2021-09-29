#include <iostream>
#include <random>
#include <cmath>
#include <string>
#define needlesize 1

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "use " << argv[0] << " [uint throws]\n";
        return 1;
    }
    uint64_t throws = std::stoull(argv[1]);
    std::random_device rd;
    std::default_random_engine gen(rd());
    // Рандом центра иглы
    std::uniform_real_distribution<double> centr(0, needlesize);
    // Рандом координат вектора угла [0; n/2)
    double radius = needlesize / 2.0;
    std::uniform_real_distribution<double> coords(0, radius);
    // кол-во пересекающих линию
    uint64_t inter = 0;
    // процент выполнения
    uint64_t percent = 0;
    for(uint64_t i = 0; i < throws; ++i)
    {
        if ((i * 100) / throws > percent)
        {
            percent = (i * 100) / throws;
            std::cout << i << "/" << throws << " (" << percent <<"%)\n";
        }
        double middle = centr(gen), x = radius, y = radius;
        // На линии
        if (middle == 0)
        {
            ++inter;
            continue;
        }
        // Для того чтобы равномерно распредилить угол
        // координаты должны распределяться внутри круга
        // координата (0, 0) не подходит, так как от неё считаем направление
        while (((x == 0) && (y == 0)) || (x * x + y * y > (radius * radius)))
        {
            x = radius - coords(gen);
            y = radius - coords(gen);
        }
        // Упала вертикально, но middle != 0
        if (x == 0) continue;
        // коэффициент угла наклона линии
        double k = y / x;
        // не сложно вывести формулу новой точки пересекающей круг радиуса (needlesize / 2)
        x = radius * sqrt(1 / (k * k + 1));
        // она же проекция на ось
        if ((middle - x) <= 0 || (middle + x) >= needlesize)
        {
            ++inter;
        }

    }
    std::cout << throws << "/" << throws << " (" << 100 <<"%)\n";
    std::cout <<2.0 * throws / inter << std::endl;
    return 0;
}
