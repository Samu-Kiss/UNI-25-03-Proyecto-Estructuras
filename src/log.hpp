#pragma once
#include "./termcolor.hpp"
#include <iostream>
#include <string>

// Formato: \t[Modulo/Estado]: Mensaje
// Colores: Exito->Verde, Info->Azul, Advertencia->Amarillo, Error->Rojo
// Flujo: Advertencia/Error -> std::cerr, Exito/Info -> std::cout


//EXTENSION DE LOGS REALIZADA CON AYUDA DE COPILOT
/*PROMPT: Analiza las salidas de consola y revisa su formato "\t[Modulo/Estado]: ..." así como sus colores (Verde, Azul, Amarillo y Rojo). Una vez analizado implementa un log helper que permita estandarizar el formato de salida que analizaste.
*/

enum class LogEstado { Exito, Info, Advertencia, Error };

inline const char* LogEstadoTexto(LogEstado e) {
    switch (e) {
        case LogEstado::Exito: return "Exito";
        case LogEstado::Info: return "Info";
        case LogEstado::Advertencia: return "Advertencia";
        case LogEstado::Error: return "Error";
    }
    return "Info";
}

inline std::ostream& LogStream(LogEstado e) {
    if (e == LogEstado::Error || e == LogEstado::Advertencia) return std::cerr;
    return std::cout;
}

inline void Log(const std::string &modulo, LogEstado estado, const std::string &mensaje) {
    using namespace termcolor;
    std::ostream &os = LogStream(estado);
    switch (estado) {
        case LogEstado::Exito:       os << green; break;
        case LogEstado::Info:        os << blue; break;
        case LogEstado::Advertencia: os << yellow; break;
        case LogEstado::Error:       os << red; break;
    }
    os << "\t[" << modulo << "/" << LogEstadoTexto(estado) << "]: " << reset << mensaje << std::endl;
}

#define LOG_EXITO(mod,msg)       Log((mod), LogEstado::Exito, (msg))
#define LOG_INFO(mod,msg)        Log((mod), LogEstado::Info, (msg))
#define LOG_ADVERTENCIA(mod,msg) Log((mod), LogEstado::Advertencia, (msg))
#define LOG_ERROR(mod,msg)       Log((mod), LogEstado::Error, (msg))
