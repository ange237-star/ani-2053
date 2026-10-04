#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    long long points = 0, segments = 0, triangles = 0, refuses = 0;

    for (int i = 0; i < n; i++) {
        std::string type;
        long long s = 0;
        std::cin >> type >> s;

        long long nombre = 0, restants = 0;
        std::string unite;

        if (type == "POINTS") {
            nombre = s;
            unite = "POINTS";
            points += nombre;
        } else if (type == "LINES") {
            nombre = s / 2;
            restants = s % 2;
            unite = "SEGMENTS";
            segments += nombre;
        } else if (type == "LINE_STRIP") {
            if (s >= 2) nombre = s - 1;
            else restants = s;
            unite = "SEGMENTS";
            segments += nombre;
        } else if (type == "TRIANGLES") {
            nombre = s / 3;
            restants = s % 3;
            unite = "TRIANGLES";
            triangles += nombre;
        } else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN") {
            if (s >= 3) nombre = s - 2;
            else restants = s;
            unite = "TRIANGLES";
            triangles += nombre;
        } else {
            std::cout << type << " " << s << " REFUSE\n";
            refuses++;
            continue;
        }

        std::cout << type << " " << s << " " << nombre << " " << unite
                  << " " << restants << "\n";
    }

    std::cout << "POINTS " << points << "\n";
    std::cout << "SEGMENTS " << segments << "\n";
    std::cout << "TRIANGLES " << triangles << "\n";
    std::cout << "REFUSES " << refuses << "\n";
    return 0;
}
