//
// Created by Anushi on 04/07/24.
//

#ifndef AMOUNT_H
#define AMOUNT_H


class Amount {
public:
    [[nodiscard]] int getRupee() const {
        return rupee;
    }

    [[nodiscard]] int getPaisa() const {
        return paisa;
    }

    Amount() {};

    Amount(int rupee, int paisa)
        : rupee(rupee),
          paisa(paisa) {
        assert(paisa < 100);
    }

    Amount operator +(Amount other) const {
        int totalPaisa = paisa + other.paisa;
        return Amount(rupee + other.rupee + (totalPaisa/100), totalPaisa % 100);
    }

    void operator +=(Amount other) {
        paisa += other.paisa;
        rupee += other.rupee + (paisa / 100);
        paisa %= 100;
    }

    Amount operator *(int value) const {
        int totalPaisa = paisa * value;
        return Amount((rupee * value) + (totalPaisa/100), totalPaisa % 100);
    }

    bool operator<(const Amount &other) const {
        if(rupee != other.rupee) return rupee < other.rupee;
        return paisa < other.paisa;
    }

    void print() const {
        std::cout<<"{"<<rupee<<","<<paisa<<"}";
    }

private:
    int rupee;
    int paisa;
};

const auto ZERO_AMOUNT = Amount(0,0);

#endif //AMOUNT_H
