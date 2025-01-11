#include <iostream>
#include <cmath>

// 基类 Shape
class Shape {
protected:
	double area;  // 面积 2D图形
	double volume; // 体积 3D图形

public:
	// 默认构造函数
	Shape(): area(0), volume(0) { }

	// 虚析构函数  这样如果是基类指针的话，也能正常的找到对应的派生类
	virtual ~Shape() {}

	// 纯虚函数 需要派生类实现
	virtual void calculateArea() = 0;
	virtual void calculateVolume() = 0;

	double getArea() const { return area; } // 获取面积
	double getVolume() const { return volume; }  // 获取体积

	virtual void display() const = 0;  // 纯虚函数，用于显示信息
};

// 方格类
class Square : public Shape {
private:
	double side;  // 边长
public:
	Square(double s) : side(s) {}  // 默认会调用基类的默认构造函数

	void calculateArea() override {
		area = side * side; // 计算方格面积
	}

	void calculateVolume() override {
		volume = 0;  // 没有体积
	}

	void display() const override {
		std::cout << "面积：" << area << ", 体积：" << volume << std::endl;
	}
};

// 圆类
class Circle: public Shape {
private:
	double radius;  // 圆的半径
public:
	Circle(double r) : radius(r) {}

	void calculateArea() override {
		area = M_PI * radius * radius;  // 计算圆的面积
	}

	void calculateVolume() override {
		volume = 0;  // 圆没有体积
	}

	void display() const override {
		std::cout << "面积：" << area << ", 体积：" << volume << std::endl;
	}
};

// 球类：Sphere
class Sphere : public Shape {
private:
	double radius;
public:
	Sphere(double r) : radius(r) {}

	void calculateArea() override {
		area = 4 * M_PI * radius * radius;  // 计算球的面积
	}

	void calculateVolume() override {
		volume = (4.0 / 3.0) * M_PI * radius * radius * radius;  // 计算球的面积
	}

	void display() const override {
		std::cout << "面积：" << area << ", 体积：" << volume << std::endl;
	}
};

// 圆锥类：Cone
class Cone : public Shape {
private:
    double radius;  // 圆锥底面的半径
    double height;  // 圆锥的高度
public:
    Cone(double r, double h) : radius(r), height(h) {}

    void calculateArea() override {
        area = M_PI * radius * (radius + sqrt(height * height + radius * radius));  // 圆锥表面积
    }

    void calculateVolume() override {
        volume = (1.0 / 3.0) * M_PI * radius * radius * height;  // 圆锥体积
    }

    void display() const override {
        std::cout << "Cone - Area: " << area << ", Volume: " << volume << std::endl;
    }
};

int main() {
    Shape* shapes[4];
    
    // 创建不同形状的实例
    shapes[0] = new Square(5);
    shapes[1] = new Circle(3);
    shapes[2] = new Sphere(4);
    shapes[3] = new Cone(3, 5);

    // 计算面积和体积，并显示结果
    for (int i = 0; i < 4; i++) {
        shapes[i]->calculateArea();
        shapes[i]->calculateVolume();
        shapes[i]->display();
    }

    // 释放内存
    for (int i = 0; i < 4; i++) {
        delete shapes[i];
    }

    return 0;
}