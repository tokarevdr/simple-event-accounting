#ifndef RESULT_H
#define RESULT_H

namespace Sea {
namespace Utils {

template<typename T, typename E>
class Result
{
public:
    Result(const T &value)
        : m_value{value}
        , m_isOk{true}
    {}

    Result(const E &error)
        : m_error{error}
        , m_isOk{false}
    {}

    bool isOk() const { return m_isOk; }

    T value() const { return m_value; }

    E error() const { return m_error; }

private:
    T m_value;
    E m_error;
    bool m_isOk;
};

} // namespace Utils
} // namespace Sea

#endif // RESULT_H
