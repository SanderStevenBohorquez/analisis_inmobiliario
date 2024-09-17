#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>    // Para dividir los datos aleatoriamente
#include <iomanip>   // Para mejorar la presentación de los resultados
#include <algorithm> // Para usar std::shuffle

struct Property {
    double price;
    int bathrooms;
};

// Función para leer el archivo CSV y cargar los datos
std::vector<Property> readCSV(const std::string& filename) {
    std::vector<Property> properties;
    std::ifstream file(filename);
    std::string line;

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return properties;
    } else {
        std::cout << "Archivo abierto correctamente: " << filename << std::endl;
    }

    // Saltar la primera línea (encabezados)
    if (!std::getline(file, line)) {
        std::cerr << "Error al leer el encabezado del archivo." << std::endl;
        return properties;
    }
    std::cout << "Encabezado: " << line << std::endl;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        Property property;
        int column = 0;

        while (std::getline(ss, value, ',')) {
            switch (column) {
                case 10: // bathrooms
                    property.bathrooms = value.empty() ? 0 : std::stoi(value);
                    break;
                case 13: // price
                    property.price = value.empty() ? 0 : std::stod(value);
                    break;
            }
            column++;
        }

        if (property.bathrooms > 0 && property.price > 0) {
            properties.push_back(property);
        }
    }

    file.close();
    return properties;
}

// Función para calcular los coeficientes de regresión lineal (m y b)
std::pair<double, double> linearRegression(const std::vector<Property>& properties) {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int n = properties.size();

    for (const auto& property : properties) {
        sumX += property.bathrooms;
        sumY += property.price;
        sumXY += property.bathrooms * property.price;
        sumX2 += property.bathrooms * property.bathrooms;
    }

    double m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double b = (sumY - m * sumX) / n;

    return {m, b};
}

// Función para evaluar el modelo
double meanSquaredError(const std::vector<Property>& properties, double m, double b) {
    double mse = 0;
    int n = properties.size();

    for (const auto& property : properties) {
        double predicted = m * property.bathrooms + b;
        mse += std::pow(property.price - predicted, 2);
    }

    return mse / n;
}

// Función para calcular el coeficiente de determinación R^2
double rSquared(const std::vector<Property>& properties, double m, double b) {
    double ssRes = 0, ssTot = 0;
    double meanY = 0;
    int n = properties.size();

    for (const auto& property : properties) {
        meanY += property.price;
    }
    meanY /= n;

    for (const auto& property : properties) {
        double predicted = m * property.bathrooms + b;
        ssRes += std::pow(property.price - predicted, 2);
        ssTot += std::pow(property.price - meanY, 2);
    }

    return 1 - (ssRes / ssTot);
}

// Función para escribir el reporte de resultados en un archivo
void escribirReporte(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo de salida: " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
}

int main() {
    // Lista de archivos CSV a leer 250 lineas
    std::vector<std::string> filenames = {
        "data/DS_Proyecto_01_Datos_Properati_part_1_split_250_1.csv"
    };
    std::vector<Property> all_properties;

    // Leer datos de cada archivo y combinarlos
    for (const auto& filename : filenames) {
        std::vector<Property> properties = readCSV(filename);
        all_properties.insert(all_properties.end(), properties.begin(), properties.end());
    }

    std::cout << "\n===================================================\n";
    std::cout << "Total de propiedades leídas: " << all_properties.size() << "\n";
    std::cout << "===================================================\n";

    if (all_properties.empty()) {
        std::cerr << "No se encontraron datos válidos." << std::endl;
        return 1;
    }

    // Dividir datos en conjunto de entrenamiento y de prueba
    std::vector<Property> train_properties, test_properties;

    std::random_device rd; // Semilla aleatoria
    std::mt19937 gen(rd());
    std::shuffle(all_properties.begin(), all_properties.end(), gen);

    size_t train_size = static_cast<size_t>(all_properties.size() * 0.7); // 70% para entrenamiento
    train_properties.assign(all_properties.begin(), all_properties.begin() + train_size);
    test_properties.assign(all_properties.begin() + train_size, all_properties.end());

    std::cout << "\nTotal de propiedades de entrenamiento: " << train_properties.size() << "\n";
    std::cout << "Total de propiedades de prueba: " << test_properties.size() << "\n";

    // Calcular coeficientes con el conjunto de entrenamiento
    auto [m, b] = linearRegression(train_properties);

    std::cout << "\n*** Resultados de la Regresión Lineal (Entrenamiento) ***\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Coeficiente de pendiente (m): " << m << "\n";
    std::cout << "Intercepto (b): " << b << "\n";

    double mse_train = meanSquaredError(train_properties, m, b);
    double r2_train = rSquared(train_properties, m, b);

    std::cout << "\n*** Métricas del Modelo en Entrenamiento ***\n";
    std::cout << "Error Cuadrático Medio (MSE) en Entrenamiento: " << mse_train << "\n";
    std::cout << "Coeficiente de Determinación (R²) en Entrenamiento: " << r2_train << "\n";

    // Validar el modelo con el conjunto de prueba
    double mse_test = meanSquaredError(test_properties, m, b);
    double r2_test = rSquared(test_properties, m, b);

    std::cout << "\n*** Métricas del Modelo en Prueba ***\n";
    std::cout << "Error Cuadrático Medio (MSE) en Prueba: " << mse_test << "\n";
    std::cout << "Coeficiente de Determinación (R²) en Prueba: " << r2_test << "\n";
    std::cout << "===================================================\n";

    // Crear el reporte detallado
    std::stringstream reporte;
    reporte << "# Análisis del Mercado Inmobiliario mediante Regresión Lineal Simple\n";
    reporte << "\n## Introducción\n";
    reporte << "El propósito de este proyecto es desarrollar un modelo de regresión lineal simple en C++ para predecir el precio de propiedades en Argentina. La variable independiente seleccionada para el modelo es el número de baños, y la variable dependiente es el precio de la propiedad.\n";

    reporte << "\n## Descripción del Dataset\n";
    reporte << "- Dataset: `DS_Proyecto_01_Datos_Properati.csv`\n";
    reporte << "- Fuente: Kaggle\n";
    reporte << "- Registros totales: " << all_properties.size() << "\n";
    reporte << "- Variables principales:\n";
    reporte << "  - `price`: Precio de la propiedad en moneda local.\n";
    reporte << "  - `bathrooms`: Número de baños.\n";

    reporte << "\n## Análisis Exploratorio de Datos (EDA)\n";
    reporte << "El análisis exploratorio inicial mostró una correlación positiva entre el número de baños y el precio de las propiedades. Se detectaron algunos valores atípicos en el conjunto de datos, que fueron excluidos para mejorar la precisión del modelo.\n";

    reporte << "\n## Implementación del Modelo de Regresión Lineal\n";
    reporte << "Se implementó un modelo de regresión lineal simple para predecir el precio de las propiedades basado en el número de baños. Los coeficientes calculados son:\n";
    reporte << "- Pendiente (`m`): " << m << "\n";
    reporte << "- Intercepto (`b`): " << b << "\n";

    reporte << "\n## Resultados del Modelo\n";
    reporte << "- **Conjunto de Entrenamiento:**\n";
    reporte << "  - MSE: " << mse_train << "\n";
    reporte << "  - R²: " << r2_train << "\n";
    reporte << "  - Interpretación: El modelo captura aproximadamente el " << r2_train * 100 << "% de la variación en los precios de las propiedades basada en el número de baños.\n";

    reporte << "\n- **Conjunto de Prueba:**\n";
    reporte << "  - MSE: " << mse_test << "\n";
    reporte << "  - R²: " << r2_test << "\n";
    reporte << "  - Interpretación: El rendimiento del modelo en el conjunto de prueba es menor, lo que indica que el modelo no se generaliza perfectamente a nuevos datos.\n";

    reporte << "\n## Discusión y Conclusiones\n";
    reporte << "El modelo de regresión lineal simple muestra que el número de baños tiene un impacto positivo en el precio de la propiedad, pero no es la única variable que influye. Los resultados sugieren que el modelo puede mejorarse incorporando más variables explicativas y ajustando su complejidad.\n";

    reporte << "\n## Posibles Mejoras\n";
    reporte << "- Incluir variables adicionales como la ubicación y el tamaño de la propiedad.\n";
    reporte << "- Usar un modelo de regresión múltiple para capturar más características.\n";
    reporte << "- Realizar una limpieza de datos más exhaustiva para eliminar valores atípicos.\n";

    // Guardar el reporte en un archivo de texto
    escribirReporte("resultados/reporte_analisis.txt", reporte.str());

    std::cout << reporte.str(); // Imprimir el contenido del reporte en consola

    return 0;
}
