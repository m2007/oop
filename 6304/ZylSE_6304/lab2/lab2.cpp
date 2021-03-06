// ConsoleApplication12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <locale.h>
using namespace std;
#define PI            3.14159265358979323846
class Point {
public:
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {}
};

class Shape {
public:
	Shape(double x, double y) :color("white"), center(x, y), angle(0) {}

	void setColor(string color) {// установка цвета
		this->color = color;
	}

	/*string getColor() {
		return color;
	}*/

	void reLocate(double x, double y) {// перемещение в другие координаты (по центру)+

		for (auto& i : points) {
			i.x += x - center.x;
			i.y += y - center.y;
		}
		center.x = x;
		center.y = y;
	}
	virtual void zoom(double n) = 0;
	void prepare_for_zoom(double& n) {// масштабирование каждой точки
		if (n<0) {
			n = abs(n);
		}
		center.x *= n;
		center.y *= n;
		for (auto& i : points) {
			i.x *= n;
			i.y *= n;
		}
	}

	void turn(int angl) {// поворот на угол
		angl = angl % 360;
		angle += angl;
		double radian = angl*PI / 180;
		for (auto& i : points) {
			double x_ = i.x*cos(radian) - i.y*sin(radian);
			double y_ = i.y*cos(radian) + i.x*sin(radian);
			i.x = x_;
			i.y = y_;
		}
	}

	virtual void printOUT(ostream& out) = 0; // печать информации о фигуре
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}


protected:
	string color;
	Point center;
	int angle;
	vector<Point> points;
};

class Square : public Shape {
public:
	Square(Point center, double side) : Shape(center.x, center.y), side(side) {
		points.push_back({ center.x - side / 2, center.y + side / 2 });
		points.push_back({ center.x + side / 2, center.y + side / 2 });
		points.push_back({ center.x + side / 2, center.y - side / 2 });
		points.push_back({ center.x - side / 2, center.y - side / 2 });
	}

	void zoom(double n) {
		prepare_for_zoom(n);
		side *= n;
	}

	void printOUT(ostream& out) {
		out << "Создан квадрат!" << endl;
		out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
		out << "Длина стороны квадрата: " << side << endl;
		out << "Точки квадрата:" << endl;
		for (const auto& i : points) {
			out << "(" << i.x << ", " << i.y << ")\n";
		}
		out << "Цвет: " << color << endl;
		out << "Угол: " << angle << endl;

	}

private:
	double side;
};


class Rhomb : public Shape {
public:
	Rhomb(Point center, double diagonal_half_1, double diagonal_half_2) : Shape(center.x, center.y), side(sqrt(pow(diagonal_half_1, 2) + pow(diagonal_half_2, 2))) {
		points.push_back({ center.x - diagonal_half_1, center.y });
		points.push_back({ center.x, center.y + diagonal_half_2 });
		points.push_back({ center.x + diagonal_half_1, center.y });
		points.push_back({ center.x , center.y - diagonal_half_2 });
	}

	void zoom(double n) {
		prepare_for_zoom(n);
		side *= n;
	}

	void printOUT(ostream& out) {
		out << "Создан ромб!" << endl;
		out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
		out << "Длина стороны ромба: " << side << endl;
		out << "Точки ромба:" << endl;
		for (const auto& i : points) {
			out << "(" << i.x << ", " << i.y << ")\n";
		}
		out << "Цвет: " << color << endl;
		out << "Угол: " << angle << endl;

	}

private:
	double side;
};

class Trapezium : public Shape {
public:
Trapezium(Point center, double side_1, double side_2, double h) : Shape(center.x, center.y), side_1(side_1), side_2(side_2), h(h) {
points.push_back({ center.x - side_1/2, center.y+h/2 });
points.push_back({ center.x + side_1 / 2, center.y + h / 2 });
points.push_back({ center.x + side_2 / 2, center.y - h / 2 });
points.push_back({ center.x - side_2 / 2, center.y - h / 2 });
}

void zoom(double n) {
prepare_for_zoom(n);
side_1 *= n;
side_2 *= n;
h *= n;
}

void printOUT(ostream& out) {
out << "Создана трапеция!" << endl;
out << "Координаты центра: (" << center.x << ", " << center.y << ")" << endl;
out << "Длина оснований трапеции: " << side_1 <<" "<<side_2 <<endl;
out << "Длина высоты: " << h << endl;
out << "Точки трапеции:" << endl;
for (const auto& i : points) {
out << "(" << i.x << ", " << i.y << ")\n";
}
out << "Цвет: " << color << endl;
out << "Угол: " << angle << endl;

}

private:
double side_1;
double side_2;
double h;
};



int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "/***********************************************/" << endl;
	cout << "/************************/" << endl;
	Square sq({ 0,0 }, 2);
	cout << sq << endl;
	cout << "/************************/" << endl;

	sq.zoom(3);
	sq.turn(180);
	sq.setColor("Green");
	cout << sq<<endl;
	cout << "/************************/" << endl;

	sq.reLocate(5.5, 7.6);
	cout << sq;
	cout << "/************************/" << endl;
	cout << "/***********************************************/" << "\n\n";


	cout << "/***********************************************/" << endl;
	cout << "/************************/" << endl;
	Rhomb rm({ 0,0 }, 2, 3);
	cout << rm;
	cout << "/************************/" << endl;

	rm.zoom(3);
	rm.turn(180);
	rm.setColor("Red");
	cout << rm << endl;
	cout << "/************************/" << endl;

	rm.reLocate(-5.5, -4.6);
	cout << rm;
	cout << "/************************/" << endl;
	cout << "/***********************************************/" << "\n\n";

	cout << "/***********************************************/" << endl;
	cout << "/************************/" << endl;
	Trapezium tr({ 0,0 }, 2, 5, 4);
	cout << tr;
	cout << "/************************/" << endl;

	tr.zoom(3);
	tr.turn(180);
	tr.setColor("Yellow");
	cout << tr << endl;
	cout << "/************************/" << endl;

	tr.reLocate(-5.5, -4.6);
	cout << tr;
	cout << "/************************/" << endl;
	cout << "/***********************************************/" << "\n\n";

	return 0;
}

