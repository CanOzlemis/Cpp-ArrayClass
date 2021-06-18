#include <iostream>
#include <string>

void fatalError(std::string);
void normalError(std::string);
template <class T, int Size>
class Array {
	T* data = nullptr;
	std::size_t sizeLocal = 0;
;
public:
	Array() { // default
		if (Size < 0) {
			fatalError(static_cast<std::string> ("The given size is not valid."));
		}
		data = new T[Size];
		for (int i = 0; i < Size; i++)
			data[i] = NULL;
		sizeLocal = 0;
	}

	Array(const Array<T, Size>& arr) { //Copy 
		if (Size != arr.size())
			fatalError(static_cast<std::string> ("Cant copy two arrays that the sizes aren't same."));

		data = new T[Size];
		int i = 0;
		for (int i = 0; i < Size; i++) {
			data[i] = arr[i];
		}

		sizeLocal = arr.getSizeLocal();
	}

	Array(const Array&& arr) { // move
		if(arr.size() != Size)
			fatalError(static_cast<std::string> ("The given size is not same size as the array."));
		*data = std::move(*arr.getArray());
		sizeLocal = arr.getSizeLocal();
	}


	Array(std::initializer_list<T> list) { // initializer list
		data = new T[Size];


		int i = 0;
		for (auto it = list.begin(); it != list.end(); it++) {
			data[i++] = *it;
			sizeLocal++;
		}
		if (i != Size) {
			for (; i < Size; i++)
				data[i] = NULL;
		}
	}

	~Array() {
		delete[] data;
		data = nullptr;
		sizeLocal = 0;
	}


	Array& operator = (const Array<T, Size>& temp) { // assignment operator

		if (Size != temp.size())
			fatalError(static_cast<std::string> ("Cant assign two arrays that the sizes aren't same."));

		if (temp.getArray() == data)
			return *this;

		delete[] data;
		*data = *temp.getArray();
		sizeLocal = temp.getSizeLocal();

		return *this;
	}


	Array& operator = (const Array<T, Size>&& temp) { // move assignment operator

		if (Size != temp.size())
			fatalError(static_cast<std::string> ("Cant assign two arrays that the sizes aren't same."));

		if (*temp.getArray() == *data)
			return *this;

		delete[] data;
		*data = std::move(*temp.getArray());
		sizeLocal = temp.getSizeLocal();

		return *this;
	}


	bool operator == (const Array<T, Size>& r) const {

		if (sizeLocal != r.getSizeLocal() || Size != r.capacity())
			return false;

		for (int i = 0; i < Size; i++) {
			if (r[i] != data[i])
				return false;
		}
		return true;
	}

	Array operator + (const int num) {
		Array<T, Size> temp(data);
		for (int i = 0; i < Size; i++)
			temp[i] += num;
		return temp;
	}

	auto begin() {
		return *data;
	}

	auto end() {
		return *data + Size - 1;
	}

	auto& operator[] (const int index) const {
		return data[index];
	}

	int size() const {

		return sizeLocal;
	}

	bool empty() {
		if (data == nullptr || sizeLocal == 0)
			return true;

		return false;
	}

	int capacity() {
		return Size;
	}

	auto& getArray() const {
		return data;
	}

	std::size_t getSizeLocal() const {
		return sizeLocal;
	}

	T front() const {
		if( data != nullptr)
			return data[0];
		return NULL;
	}

	T back() const {
		if (data != nullptr)
			return data[sizeLocal - 1];
		return NULL;
	}

	friend std::ostream& operator << (std::ostream& out, Array arr) {
		auto temp = arr.getArray();
		for (int i = 0; i < Size; i++)
			std::cout << temp[i] << ", ";
		return out;
	}


};

void fatalError(std::string text) {
	std::cout << "\n\tERROR: " << text << std::endl;
	exit(0);
}


int main() {
	Array<std::string, 5> x = { "H", "e", "l" };
	Array<std::string, 5> y = { "W", "o", "r", "l", "d" };
	std::cout << "size for x : " << x.size() << std::endl;
	std::cout << "size for y : " << y.size() << std::endl;
	std::cout << "is equal (as items): " << (x == y) << std::endl; // size MUST BE THE SAME AT BOTH FOR THIS TO WORK
	std::cout << "Array x : " << x << std::endl;
	std::cout << "Array y : " << y << std::endl;
	std::cout << "y.front() : " << y.front() << std::endl;
	std::cout << "y.back() : " << y.back() << std::endl;
}