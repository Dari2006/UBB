#include "Activitate.h"
#include <vector>

class Planificare {
private:
    std::vector<Activitate> plan;
public:
 
    Planificare() = default;

    void adauga(const Activitate& a) {
        plan.push_back(a);
    }

    void goleste() noexcept{
        plan.clear();
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