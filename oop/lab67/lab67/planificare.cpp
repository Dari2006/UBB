#include <fstream>
#include "planificare.h"

void Planificare::exportaCSV(const std::string& numeFisier) const {
    std::ofstream out(numeFisier, std::ios::trunc);
    if (!out.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul " + numeFisier);
    }
    for (const auto& a : plan) {
        out << a.getTitlu() << "," << a.getDescriere() << "," << a.getTip() << "," << a.getDurata() << "\n";
    }
    out.close();
}

void Planificare::exportaHTML(const std::string& numeFisier) const {
    std::ofstream out(numeFisier, std::ios::trunc);
    if (!out.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul " + numeFisier);
    }
    out << "<html><body><table border=\"1\">\n";
    for (const auto& a : plan) {
        out << "<tr>\n";
        out << "<td>" << a.getTitlu() << "</td>\n";
        out << "<td>" << a.getDescriere() << "</td>\n";
        out << "<td>" << a.getTip() << "</td>\n";
        out << "<td>" << a.getDurata() << "</td>\n";
        out << "</tr>\n";
    }
    out << "</table></body></html>\n";
    out.close();
}