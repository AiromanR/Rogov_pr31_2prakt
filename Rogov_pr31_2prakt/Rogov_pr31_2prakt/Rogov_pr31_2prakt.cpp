#include <iostream>

//Структура данных о погоде
struct WeatherData {
    float temperature;
    float humidity;
    float windSpeed;
};

// Класс для работы с графом
class Graph {
private:
    int* vertices;
    int vertexCount;
    int vertexCapacity;

    struct Edge {
        int vertex1;
        int vertex2;
    };

    Edge* edges;
    int edgeCount;
    int edgeCapacity;

public:
    Graph() {
        vertexCapacity = 30;
        edgeCapacity = 30;
        vertices = new int[vertexCapacity];
        edges = new Edge[edgeCapacity];
        vertexCount = 0;
        edgeCount = 0;
    }

    //Добавление вершины
    void addVertex(int vertex) {
        //Проверяем, есть ли уже такая вершина
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == vertex) {
                return;
            }
        }

        vertices[vertexCount] = vertex;
        vertexCount++;
    }

    //Добавление ребра
    void addEdge(int vertex1, int vertex2) {
        addVertex(vertex1);
        addVertex(vertex2);

        // Проверяем, есть ли уже такое ребро
        for (int i = 0; i < edgeCount; i++) {
            if ((edges[i].vertex1 == vertex1 && edges[i].vertex2 == vertex2) ||
                (edges[i].vertex1 == vertex2 && edges[i].vertex2 == vertex1)) {
                return;
            }
        }

        edges[edgeCount].vertex1 = vertex1;
        edges[edgeCount].vertex2 = vertex2;
        edgeCount++;
    }

    //Удаление ребра
    void removeEdge(int vertex1, int vertex2) {
        for (int i = 0; i < edgeCount; i++) {
            if ((edges[i].vertex1 == vertex1 && edges[i].vertex2 == vertex2) ||
                (edges[i].vertex1 == vertex2 && edges[i].vertex2 == vertex1)) {
                //Сдвигаем все элементы после найденного
                for (int j = i; j < edgeCount - 1; j++) {
                    edges[j] = edges[j + 1];
                }
                edgeCount--;
                break;
            }
        }
    }

    //Показать граф
    void displayGraph() {
        std::cout << "Вершины: ";
        for (int i = 0; i < vertexCount; i++) {
            std::cout << vertices[i] << " ";
        }
        std::cout << "\nРёбра: ";
        for (int i = 0; i < edgeCount; i++) {
            std::cout << "(" << edges[i].vertex1 << "-" << edges[i].vertex2 << ") ";
        }
        std::cout << std::endl;
    }

    ~Graph() {
        delete[] vertices;
        delete[] edges;
    }
};

//Функция для проверки уникальности
bool isUnique(int** matrix, int rows, int cols, int currentRow) {
    for (int i = 0; i < rows; i++) {
        if (i == currentRow) continue;

        bool isEqual = true;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != matrix[currentRow][j]) {
                isEqual = false;
                break;
            }
        }
        if (isEqual) {
            return false;
        }
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "");
    //N1
    //Создайте новый массив, содержащий только четные элементы из исходного массива.
    int length;
    std::cout << "Введите длину массива: ";
    std::cin >> length;

    int* arr = new int[length];
    int evenCount = 0;

    //Ввод массива
    for (int i = 0; i < length; i++) {
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> arr[i];
        if (arr[i] % 2 == 0) {
            evenCount++;
        }
    }

    //Создание массива чётных
    int* evenArr = new int[evenCount];
    int index = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] % 2 == 0) {
            evenArr[index] = arr[i];
            index++;
        }
    }

    //Вывод результатов
    std::cout << "Оригинальный массив: ";
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nМассив из чётных: ";
    for (int i = 0; i < evenCount; i++) {
        std::cout << evenArr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    delete[] evenArr;

    //N2
    //Создайте новый многомерный массив, содержащий только уникальные строки из исходного массива.
    int rows, cols;
    std::cout << "Введите число строк в матрице: ";
    std::cin >> rows;
    std::cout << "Введите число колонок в матрице: ";
    std::cin >> cols;

    //Создание и заполнение массива(каждое число отдельной строкой)
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        std::cout << "Данные в строке " << i + 1 << ": ";
        for (int j = 0; j < cols; j++) {
            std::cin >> matrix[i][j];
        }
    }

    //Подсчет уникальных строк
    int uniqueRowsCount = 0;
    for (int i = 0; i < rows; i++) {
        if (isUnique(matrix, rows, cols, i)) {
            uniqueRowsCount++;
        }
    }

    //Создание нового массива с уникальными строками
    int** uniqueMatrix = new int* [uniqueRowsCount];
    int uniqueIndex = 0;

    for (int i = 0; i < rows; i++) {
        if (isUnique(matrix, rows, cols, i)) {
            uniqueMatrix[uniqueIndex] = new int[cols];
            for (int j = 0; j < cols; j++) {
                uniqueMatrix[uniqueIndex][j] = matrix[i][j];
            }
            uniqueIndex++;
        }
    }

    //Вывод результатов
    std::cout << "Оригинальная матрица:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Только уникальные строки:\n";
    for (int i = 0; i < uniqueRowsCount; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << uniqueMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    delete[] matrix;
    delete[] uniqueMatrix;

    //N3
    //Создайте структуру "WeatherData" с полями "temperature" (вещественное число), "humidity" (вещественное число) и "windSpeed" (вещественное число). 
    //Напишите программу на C++, которая визуализирует данные о погоде.

    int numOfData = 0;
    int maxData = 5;//прост 5
    WeatherData* weatherArray = new WeatherData[maxData];
    int choice;

    do {
        std::cout << "\n1. Добавить погодную информацию\n";
        std::cout << "2. Показать погодную информацию\n";
        std::cout << "3. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (numOfData < maxData) {
                std::cout << "Данные о погоде " << numOfData + 1 << std::endl;
                std::cout << "Температура: ";
                std::cin >> weatherArray[numOfData].temperature;
                std::cout << "Влажность: ";
                std::cin >> weatherArray[numOfData].humidity;
                std::cout << "Скорость ветра: ";
                std::cin >> weatherArray[numOfData].windSpeed;
                numOfData++;
                std::cout << "Данные о погоде добавлены\n";
            }
            else {
                std::cout << "Превышено количество дат\n";
            }
            break;

        case 2:
            if (numOfData == 0) {
                std::cout << "Нет информации\n";
            }
            else {
                std::cout << "\n=== Визуализация ===\n";
                for (int i = 0; i < numOfData; i++) {
                    std::cout << "\nДата " << i + 1 << ":\n";
                    std::cout << "Температура: " << weatherArray[i].temperature << "°C\n";

                    //Визуализация температуры
                    std::cout << "Температура: ";
                    int tempBars = (int)(std::abs(weatherArray[i].temperature));
                    for (int j = 0; j < tempBars; j++) {
                        if (weatherArray[i].temperature > 0) {
                            std::cout << "+";
                        }
                        else {
                            std::cout << "-";
                        }
                    }
                    std::cout << std::endl;

                    std::cout << "Влажность: " << weatherArray[i].humidity << "%\n";
                    //Визуализация влажности
                    std::cout << "Влажность: ";
                    int humidityBars = (int)(weatherArray[i].humidity / 10);
                    for (int j = 0; j < humidityBars; j++) {
                        std::cout << "#";
                    }
                    std::cout << std::endl;

                    std::cout << "Скорость ветра: " << weatherArray[i].windSpeed << " m/s\n";
                    //Визуализация скорости ветра
                    std::cout << "Ветер: ";
                    int windBars = (int)(weatherArray[i].windSpeed);
                    for (int j = 0; j < windBars; j++) {
                        std::cout << ">";
                    }
                    std::cout << std::endl;
                }
            }
            break;

        case 3:
            break;

        default:
            std::cout << "Введите из доступных вариантов!\n";
        }
    } while (choice != 3);

    delete[] weatherArray;

    //N4
    //Создайте класс "Graph" с приватными полями "vertices" (массив вершин) и "edges" (массив ребер)
    //и публичными методами для добавления и удаления ребер в графе.

    Graph graph;
    int graphChoice;

    do {
        std::cout << "\n1. Добавить вершину\n";
        std::cout << "2. Добавить ребро\n";
        std::cout << "3. Удалить ребро\n";
        std::cout << "4. Показать граф\n";
        std::cout << "5. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> graphChoice;

        switch (graphChoice) {
        case 1: {
            int vertex;
            std::cout << "Введите вершину: ";
            std::cin >> vertex;
            graph.addVertex(vertex);
            std::cout << "Вершина добавлена\n";
            break;
        }
        case 2: {
            int v1, v2;
            std::cout << "Введите первую вершину: ";
            std::cin >> v1;
            std::cout << "Введите вторую вершину: ";
            std::cin >> v2;
            graph.addEdge(v1, v2);
            std::cout << "Ребро добавлено\n";
            break;
        }
        case 3: {
            int v1, v2;
            std::cout << "Введите первую вершину: ";
            std::cin >> v1;
            std::cout << "Введите вторую вершину: ";
            std::cin >> v2;
            graph.removeEdge(v1, v2);
            std::cout << "Ребро удалено!\n";
            break;
        }
        case 4:
            graph.displayGraph();
            break;
        case 5:
            break;
        default:
            std::cout << "Введите доступный вариант\n";
        }
    } while (graphChoice != 5);

    return 0;
}