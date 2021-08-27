#include <cmath>
#include <iostream>
#include <string> 
#include <vector>
using namespace std;

class Vector2
{
public:
    double x;
    double y;

    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    };

    float Length() {
        return sqrt(x * x + y * y);
    };

    Vector2 Normalize() {
        float length = Length();
        return Vector2(x / length, y / length);
    };

    static float Dot(Vector2 v1, Vector2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    };

    static float Distance(Vector2 v1, Vector2 v2) {
        return (v1 - v2).Length();
    };

    static Vector2 Read(std::string text) {
        cout << text << "\n";
        float _x, _y;
        cout << "Type x\n";
        cin >> _x;
        cout << "Type y\n";
        cin >> _y;
        return Vector2(_x, _y);
    }

    static float Angle(Vector2 v1, Vector2 v2) {
        if (v1.Length() == 0 || v2.Length() == 0) return 0;
        float dot = Vector2::Dot(v1, v2);
        float cos = dot / v1.Length() / v2.Length();
        return abs(acos(cos) * 180 / M_PI);
    }

    Vector2 operator - (const Vector2 v2) {
        return Vector2(x - v2.x, y - v2.y);
    };

    Vector2 operator + (const Vector2 v2) {
        return Vector2(x + v2.x, y + v2.y);
    };
};

class Person
{
public:
    Vector2 position;
    Vector2 direction;
    float distanceOfView;
    float angleOfView;
    int peopleInFieldOfViewCount = 0;

    Person(Vector2 _position, Vector2 _direction)
        : position{ _position }, direction{ _direction } {}

    static Person Read(std::string text) {
        cout << text << "\n";
        Vector2 _position = Vector2::Read("Type position");
        Vector2 _direction = Vector2::Read("Type direction").Normalize();
        return Person(_position, _direction);
    }

    bool IsInFieldOfView(Person person) {
        float distance = Vector2::Distance(position, person.position);
        Vector2 directionToPerson = (person.position - position).Normalize();
        float angle = Vector2::Angle(direction, directionToPerson);
        return angle < angleOfView / 2 && distance < distanceOfView;
    };
};

int main() {

    float distanceOfView;
    cout << "Type distance of view\n";
    cin >> distanceOfView;

    float angleOfView;
    cout << "Type angle of view\n";
    cin >> angleOfView;

    int peopleCount;
    cout << "Type people count\n";
    cin >> peopleCount;

    vector<Person> people;

    for (int i = 0; i < peopleCount; i++) {
        Person person = Person::Read("Initialize Person " + std::to_string(i + 1));
        person.distanceOfView = distanceOfView;
        person.angleOfView = angleOfView;
        people.push_back(person);
    }

    for (int i = 0; i < peopleCount; i++) {
        for (int j = 0; j < peopleCount; j++) {
            if (i == j) continue;
            bool isInFieldOfView = people[i].IsInFieldOfView(people[j]);
            if (isInFieldOfView) people[i].peopleInFieldOfViewCount++;
        }

        cout << "Person " << (i + 1) << " sees " << people[i].peopleInFieldOfViewCount << " people.\n";
    }

    return 0;
}