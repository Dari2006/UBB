#pragma once
#include "Activitate.h"
#include "observer.h"
#include <vector>

class Planificare: public Observable{
private:
    std::vector<Activitate> plan;
public:
 
    Planificare() = default;

    void adauga(const Activitate& a) {
        plan.push_back(a);
        notify();
    }

    void goleste() noexcept{
        plan.clear();
        notify();
    }

    void adaugaToate(const std::vector<Activitate>& activitatiNoi) {
        plan.insert(plan.end(), activitatiNoi.begin(), activitatiNoi.end());

        notify();
    }

    const std::vector<Activitate>& getToate() const noexcept{
        return plan;
    }

    size_t dim() const noexcept{
        return plan.size();
    }
    void exportaCSV(const string& numeFisier) const;
    void exportaHTML(const string& numeFisier) const;
};

