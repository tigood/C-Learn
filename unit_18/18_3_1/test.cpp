/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-02 23:51:20
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-03 21:54:07
 * @FilePath: /C++Primer/unit_18/18_3_1/test.cpp
 * @Description: 继承
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <string>

// 虚基类
class ZooAnimal
{
public:
    ZooAnimal(const std::string &name, bool onExhibit, const std::string &type)
        : name_(name), onExhibit_(onExhibit), type_(type)
    {
        std::cout << "ZooAnimal constructed: " << type_ << " (" << name_ << ")\n";
    }

protected:
    std::string name_;
    bool        onExhibit_;
    std::string type_;
};

// 虚继承 ZooAnimal
class Bear : virtual public ZooAnimal
{
public:
    Bear(const std::string &name, bool onExhibit) : ZooAnimal(name, onExhibit, "Bear")
    {
        std::cout << "Bear constructed\n";
    }
};

// 虚继承 ZooAnimal
class Raccoon : virtual public ZooAnimal
{
public:
    Raccoon(const std::string &name, bool onExhibit)
        : ZooAnimal(name, onExhibit, "Raccoon")
    {
        std::cout << "Raccoon constructed\n";
    }
};

// 普通类
class Endangered
{
public:
    enum Level
    {
        normal,
        critical
    };

    Endangered(Level level) : level_(level)
    {
        std::cout << "Endangered constructed, level = "
                  << (level == critical ? "critical" : "normal") << "\n";
    }

protected:
    Level level_;
};

// 最底层派生类
class Panda : public Bear, public Raccoon, public Endangered
{
public:
    Panda(const std::string &name, bool onExhibit)
        : ZooAnimal(name, onExhibit, "Panda"), // 虚基类由最底层派生类 Panda 初始化
          Bear(name, onExhibit),               // 虚基类部分不会再次初始化
          Raccoon(name, onExhibit),
          Endangered(Endangered::critical),
          sleeping_flag(false)
    {
        std::cout << "Panda constructed\n";
    }

private:
    bool sleeping_flag;
};

int main()
{
    std::cout << "--- Create Bear ---\n";
    Bear b("Baloo", true);
    std::cout << "\n--- Create Raccoon ---\n";
    Raccoon r("Rocky", false);
    std::cout << "\n--- Create Panda ---\n";
    Panda p("Po", true);

    return 0;
}
