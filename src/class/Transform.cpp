#include "class/Transform.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <string>

namespace Peep {

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

bool Vector2::operator==(const Vector2 &other) const {
    return fabs(x - other.x) < 0.0001f && fabs(y - other.y) < 0.0001f;
}

std::ostream& operator<<(std::ostream& os, const Vector2& t) {
    return os << "Vector2(" << t.x << ", " << t.y << ")";
}

std::string Vector2::ToString() const {
    return "Vector2( " + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Scale::Scale() : w(0), h(0) {}
Scale::Scale(float w, float h) : w(w), h(h) {}

bool Scale::operator==(const Scale &other) const {
    return fabs(w - other.w) < 0.0001f && fabs(h - other.h) < 0.0001f;
}

std::ostream& operator<<(std::ostream& os, const Scale& t) {
    return os << "Scale(" << t.w << ", " << t.h << ")";
}

std::string Scale::ToString() const {
    return "Scale( " + std::to_string(w) + ", " + std::to_string(h) + ")";
}

void Transform::UpdateRect() {
    rect_.x = position_.x;
    rect_.y = position_.y;
    rect_.w = scale_.w;
    rect_.h = scale_.h;
}

Transform::Transform() : position_(Vector2()), scale_(Scale()) {
    UpdateRect();
}

Transform::Transform(float x, float y)
    : position_{ x, y }, scale_{ 0, 0 }, rect_{ x, y, 0, 0 } {
    UpdateRect();
}

Transform::Transform(float x, float y, float w, float h)
    : position_{ x, y }, scale_{ w, h }, rect_{ x, y, w, h } {
    UpdateRect();
}

Transform::Transform(Vector2 pos, Scale scl)
    : position_(pos), scale_(scl), rect_{ pos.x, pos.y, scl.w, scl.h } {
    UpdateRect();
}

// getters
const Vector2 &Transform::GetPos() const noexcept { return position_; }
const Scale &Transform::GetScl() const noexcept { return scale_; }
const SDL_FRect &Transform::GetRect() const noexcept { return rect_; }

bool Transform::operator==(const Transform &other) const {
    return GetPos() == other.GetPos() &&
           GetScl() == other.GetScl();
}

// setters
void Transform::SetPosition(float x, float y) {
    position_.x = x;
    position_.y = y;
    UpdateRect();
}

void Transform::SetPosition(Vector2 vector) {
    position_ = vector;
    UpdateRect();
}

void Transform::SetPositionX(float x) {
    position_.x = x;
    UpdateRect();
}

void Transform::SetPositionY(float y) {
    position_.y = y;
    UpdateRect();
}

void Transform::AddPositionX(float x) {
    position_.x += x;
    UpdateRect();
}

void Transform::AddPositionY(float y) {
    position_.y += y;
    UpdateRect();
}
    
void Transform::SetScale(float w, float h) {
    scale_.w = w;
    scale_.h = h;
    UpdateRect();
}

void Transform::SetScale(Scale scl) {
    scale_ = scl;
    UpdateRect();
}

void Transform::SetScaleW(float w) {
    scale_.w = w;
    UpdateRect();
}

void Transform::SetScaleH(float h) {
    scale_.h = h;
    UpdateRect();
}

void Transform::ApplyOffset(const Transform &off) {
    position_.x += off.GetPos().x;
    position_.y += off.GetPos().y;
    scale_.w += off.GetScl().w;
    scale_.h += off.GetScl().h;
    UpdateRect();
}

std::ostream& operator<<(std::ostream& os, const Transform& t) {
    return os << "Transform({" << std::endl <<
        "\tposition.x: " << t.GetPos().x << std::endl <<
        "\tposition.y: " << t.GetPos().y << std::endl <<
    "}, {" << std::endl <<
        "\tscale.w: " << t.GetScl().w << std::endl <<
        "\tscale.h: " << t.GetScl().h << std::endl <<
    "})"; 
}

std::string Transform::ToString() const {
    return "Transform( " + std::to_string(position_.x) + ", " + std::to_string(position_.y) + ", " + std::to_string(scale_.w) + ", " + std::to_string(scale_.h) + ")";
}

}