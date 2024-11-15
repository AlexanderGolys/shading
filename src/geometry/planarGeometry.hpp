#pragma once
#include "src/fundamentals/func.hpp"
// #include "smoothParametric.hpp"


class SmoothParametricCurve;

class SmoothParametricPlaneCurve {
    Foo12 _f;
    Foo12 _df;
    Foo12 _ddf;
    std::function<Foo12(int)> _der_higher = [this](int n)
            {return n == 0 ? _f : n == 1 ? _df : n == 2 ? _ddf : derivativeOperator(_der_higher(n-1), this->eps);};
    float eps = 0.01;
    RP1 t0 = std::nullopt;
    RP1 t1 = std::nullopt;
    bool periodic = true;
public:
	explicit SmoothParametricPlaneCurve(const Foo12& curve, float t0=0, float t1=TAU, bool period=true, float epsilon=0.01);
    SmoothParametricPlaneCurve(Foo12 f,const Foo12& df, float t0=0, float t1=TAU, bool period=true, float epsilon=0.01);
    SmoothParametricPlaneCurve(Foo12 f, Foo12 df, Foo12 ddf,
                               float t0 = 0, float t1 = TAU, bool period = true, float epsilon = 0.01);
    SmoothParametricPlaneCurve(const SmoothParametricPlaneCurve &other);
    SmoothParametricPlaneCurve(SmoothParametricPlaneCurve &&other) noexcept;
    SmoothParametricPlaneCurve &operator=(const SmoothParametricPlaneCurve &other);
    SmoothParametricPlaneCurve &operator=(SmoothParametricPlaneCurve &&other) noexcept;
    glm::vec2 operator()(float t) const { return _f(t); }
    glm::vec2 derivative(float t) const { return _df(t); }
    glm::vec2 df(float t) const { return derivative(t); }
    glm::vec2 second_derivative(float t) const { return _ddf(t); }
    glm::vec2 ddf(float t) const { return second_derivative(t); }
    glm::vec2 higher_derivative(float t, int n) const { return _der_higher(n)(t); }
    glm::vec2 tangent(float t) const { return normalise(_df(t)); }
    glm::vec2 normal(float t) const { return orthogonalComplement(tangent(t)); }
	std::vector<glm::vec2> sample(float t0, float t1, int n) const;
	std::vector<glm::vec2> sample(int n) const {return sample(t0.value_or(-1), t1.value_or(1), n);}
	std::vector<glm::vec3> adjacency_lines_buffer(float t0, float t1, int n, float z=0) const;
    SmoothParametricCurve embedding(glm::vec3 v1=e1, glm::vec3 v2=e2, glm::vec3 pivot=ORIGIN) const;
    glm::vec2 bounds() const { return glm::vec2(t0.value_or(-1), t1.value_or(1)); }
  bool isPeriodic() const { return periodic; }
};