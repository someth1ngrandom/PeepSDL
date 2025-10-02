#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include <ostream>

namespace Peep {

struct Vector2 {
    float x, y;

    Vector2();
    Vector2(float x, float y);

    bool operator==(const Vector2 &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector2& t);
    std::string ToString() const;
};

struct Scale {
    float w, h;

    Scale();
    Scale(float w, float h);

    bool operator==(const Scale &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Scale& t);
    std::string ToString() const;
};

struct Transform {
private:
    Vector2 position_;
    Scale scale_;
    SDL_FRect rect_;

    void UpdateRect();
public:
    Transform();

    Transform(float x, float y);
    Transform(float x, float y, float w, float h);

    Transform(Vector2 pos, Scale scl);

    // getters
    const Vector2 &GetPos() const noexcept;
    const Scale &GetScl() const noexcept;
    const SDL_FRect &GetRect() const noexcept;

    bool operator==(const Transform &other) const;

    // setters
    void SetPosition(float x, float y);
    void SetPosition(Vector2 vector);

    void SetPositionX(float x);
    void SetPositionY(float y);

    void AddPositionX(float x);
    void AddPositionY(float y);
    
    void SetScale(float w, float h);
    void SetScale(Scale scl);

    void SetScaleW(float w);
    void SetScaleH(float h);

    void ApplyOffset(const Transform &offset);

    friend std::ostream& operator<<(std::ostream& os, const Transform& t);
    std::string ToString() const;
};

std::ostream& operator<<(std::ostream& os, const Transform& t);

}