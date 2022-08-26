#pragma once

#define PROPERTY_RW(type, name) \
public: \
const type& name() const noexcept { return _##name; } \
type& name() noexcept { return _##name; } \
void set_##name(const type& value) noexcept { _##name = value; }\
private: \
type _##name

#define PROPERTY_RO(type, name) \
public: \
const type& name() const noexcept { return _##name; } \
protected: \
type& name() noexcept { return _##name; } \
void set_##name(const type& value) noexcept { _##name = value; }\
private: \
type _##name