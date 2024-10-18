#include <iostream>
#include <vector>
#include <chrono>

class SpecialMember
{
	std::vector<std::string> data_;
	size_t	sizeV_{ 999'999 };

public:
	SpecialMember();
	SpecialMember(const size_t sizeV) noexcept;

	SpecialMember(const SpecialMember& other) noexcept;
	SpecialMember(SpecialMember&& other) noexcept;

	~SpecialMember();

	size_t getSizeVec() noexcept;
	SpecialMember& operator= (const SpecialMember& other) noexcept;
	SpecialMember& operator= (SpecialMember&& other) noexcept;
};

SpecialMember::SpecialMember()
{
	std::cout << "Default constructor\n";
	data_.resize(sizeV_);
}

SpecialMember::SpecialMember(const size_t sizeV) noexcept
	: sizeV_(sizeV)
{
	std::cout << "Parameterized constructor\n";
	data_.resize(sizeV_);
}

SpecialMember::SpecialMember(const SpecialMember& other) noexcept
	:data_(other.data_), sizeV_(other.sizeV_)
{
	std::cout << "Copy constructor\n";
}

SpecialMember::SpecialMember(SpecialMember&& other) noexcept
	: data_(std::move(other.data_)), sizeV_(other.sizeV_)
{
	std::cout << "Move constructor\n";
	other.sizeV_ = 0;
}

SpecialMember::~SpecialMember()
{
	std::cout << "Destructor\n";
}

size_t SpecialMember::getSizeVec() noexcept
{
	return data_.size();
}

SpecialMember& SpecialMember::operator=(const SpecialMember& other) noexcept
{
	std::cout << "Copy assignment operator\n";
	if (this != &other)
	{  
		data_ = other.data_;      
		sizeV_ = other.sizeV_;
	}
	return *this;
}

SpecialMember& SpecialMember::operator=(SpecialMember&& other) noexcept
{
	std::cout << "Move assignment operator\n";
	if (this != &other)
	{  
		data_.clear();

		data_ = std::move(other.data_);
		sizeV_ = other.sizeV_;
		other.sizeV_ = 0;
	}
	return *this;
}

static void separator() noexcept
{
	std::string sep(25, '-');
	std::cout << sep << std::endl;
}

int main()
{
	std::cout << "Hello World!\n";
	separator();

	auto time1 = std::chrono::high_resolution_clock::now();
	SpecialMember member;
	auto time2 = std::chrono::high_resolution_clock::now();
	std::cout << "Member size no.1: " << member.getSizeVec() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count()<< " microseconds\n";
	separator();

	time1 = std::chrono::high_resolution_clock::now();
	SpecialMember member2(100);
	time2 = std::chrono::high_resolution_clock::now();
	std::cout << "Member size no.2: " << member2.getSizeVec() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << " microseconds\n";
	separator();

	time1 = std::chrono::high_resolution_clock::now();
	SpecialMember member3(member);
	std::cout << "Member size no.3: " << member3.getSizeVec() << std::endl;
	time2 = std::chrono::high_resolution_clock::now();
	std::cout  << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << " microseconds\n";
	separator();

	time1 = std::chrono::high_resolution_clock::now();
	SpecialMember member4(std::move(member3));
	time2 = std::chrono::high_resolution_clock::now();
	std::cout << "Member size no.3: " << member3.getSizeVec() << std::endl;
	std::cout << "Member size no.4: " << member4.getSizeVec() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << " microseconds\n";
	separator();

	SpecialMember member5(5);
	std::cout << "Member size no.5: " << member5.getSizeVec() << std::endl;
	time1 = std::chrono::high_resolution_clock::now();
	member5 = member4;
	time2 = std::chrono::high_resolution_clock::now();
	std::cout << "Member size no.4: " << member4.getSizeVec() << std::endl;
	std::cout << "Member size no.5: " << member5.getSizeVec() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << " microseconds\n";
	separator();

	SpecialMember member6(5);
	std::cout << "Member size no.6: " << member6.getSizeVec() << std::endl;
	time1 = std::chrono::high_resolution_clock::now();
	member6 = std::move(member4);
	time2 = std::chrono::high_resolution_clock::now();
	std::cout << "Member size no.4: " << member4.getSizeVec() << std::endl;
	std::cout << "Member size no.6: " << member6.getSizeVec() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << " microseconds\n";
	separator();
}
