#pragma once
#include <iostream>
#include <memory>

template <typename T>
class SharedPtr
{
	T* data = nullptr;
	unsigned* pointersCount = nullptr;

	void free();
	void copyFrom(const SharedPtr<T>& other);
	void move(SharedPtr<T>&& other) noexcept;

public:
	SharedPtr(T* data = nullptr);

	SharedPtr(const SharedPtr<T>& other);
	SharedPtr& operator=(const SharedPtr<T>& other);

	SharedPtr(SharedPtr<T>&& other) noexcept;
	SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;

	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();

	T* get();
	void reset(T* data = nullptr);
	size_t getCount() const;

	explicit operator bool() const;

	~SharedPtr();
};

template <typename T>
void SharedPtr<T>::free() {
	if (data == nullptr && pointersCount == nullptr)
		return;

	if (*pointersCount == 1) {
		delete data;
		delete pointersCount;
	}
	else
		(*pointersCount)--;
}

template <typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other) {
	data = other.data;
	pointersCount = other.pointersCount;
	if (data)
		(*pointersCount)++;
}

template<typename T>
void SharedPtr<T>::move(SharedPtr<T>&& other) noexcept {
	data = other.data;
	pointersCount = other.pointersCount;

	other.data = nullptr;
	other.pointersCount = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* data) {
	this->data = data;
	if (this->data)
		pointersCount = new unsigned(1);
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
	copyFrom(other);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr<T>(SharedPtr<T>&& other) noexcept {
	move(std::move(other));
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) {
	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}


template <typename T>
const T& SharedPtr<T>::operator*() const {
	if (data == nullptr)
		throw std::runtime_error("Pointer not set");

	return *data;
}

template <typename T>
T& SharedPtr<T>::operator*() {
	if (data == nullptr)
		throw std::runtime_error("Pointer not set");

	return *data;
}

template<typename T>
T* SharedPtr<T>::operator->() {
	return data;
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
	return data;
}

template<typename T>
T* SharedPtr<T>::get() {
	return data;
}

template<typename T>
void SharedPtr<T>::reset(T* data) {
	if (this->data == data) {
		return;
	}

	free();
	this->data = data;
	if (this->data) {
		pointersCount = new size_t(1);
	}
}

template<typename T>
size_t SharedPtr<T>::getCount() const {
	return pointersCount;
}

template<typename T>
SharedPtr<T>::operator bool() const {
	return data;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
	free();
}
