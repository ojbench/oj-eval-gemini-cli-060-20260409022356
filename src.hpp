#include <vector>

template <typename T>
class Expectation {
private:
    T value;
    bool result;
    bool is_not;

public:
    Expectation(const T& val) : value(val), result(true), is_not(false) {}

    Expectation& toBe(const T& y) {
        bool cond = (value == y);
        if (is_not) cond = !cond;
        result = result && cond;
        return *this;
    }

    Expectation& toBeOneOf(const std::vector<T>& y) {
        bool cond = false;
        for (size_t i = 0; i < y.size(); ++i) {
            if (value == y[i]) {
                cond = true;
                break;
            }
        }
        if (is_not) cond = !cond;
        result = result && cond;
        return *this;
    }

    Expectation& le(const T& y) {
        bool cond = (value < y) || (value == y);
        if (is_not) cond = !cond;
        result = result && cond;
        return *this;
    }

    Expectation& ge(const T& y) {
        bool cond = !(value < y);
        if (is_not) cond = !cond;
        result = result && cond;
        return *this;
    }

    Expectation& lt(const T& y) {
        bool cond = (value < y);
        if (is_not) cond = !cond;
        result = result && cond;
        return *this;
    }

    Expectation& gt(const T& y) {
        bool cond = !(value < y) && !(value == y);
        if (is_not) cond = !cond;
        result = result && cond;
        return *this;
    }

    Expectation& Not() {
        is_not = !is_not;
        return *this;
    }

    operator bool() const {
        return result;
    }
};

template <typename T>
Expectation<T> expect(const T& x) {
    return Expectation<T>(x);
}
