#include <iostream>
#include <vector>

class SpecialMember
{
	std::vector<std::string> data_;
	size_t	sizeV_{ 1'000'000 };
	std::string word_{ "SpecialMember" };

public:
	SpecialMember();
	SpecialMember(const size_t sizeV) noexcept;
	SpecialMember(const std::string word) noexcept;

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
	std::fill(data_.begin(), data_.end(), word_);
}

SpecialMember::SpecialMember(const size_t sizeV) noexcept
	: sizeV_(sizeV)
{
	std::cout << "Parameterized constructor\n";
	data_.resize(sizeV_);
	std::fill(data_.begin(), data_.end(), word_);
}

SpecialMember::SpecialMember(const std::string word) noexcept
{
}

SpecialMember::SpecialMember(const SpecialMember& other) noexcept
	:data_(other.data_), sizeV_(other.sizeV_), word_(other.word_)
{
	std::cout << "Copy constructor\n";
}

SpecialMember::SpecialMember(SpecialMember&& other) noexcept
	: data_(std::move(other.data_)), sizeV_(other.sizeV_), word_(std::move(other.word_))
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
		word_ = other.word_;      
	}
	return *this;
}

SpecialMember& SpecialMember::operator=(SpecialMember&& other) noexcept
{
	std::cout << "Move assignment operator\n";
	if (this != &other) {  
		data_.clear();
		word_.clear();

		data_ = std::move(other.data_);
		sizeV_ = other.sizeV_;
		other.sizeV_ = 0;
		word_ = std::move(other.word_);
	}
	return *this;
}

int main()
{
	std::cout << "Hello World!\n";
	std::cout << "-------------------------------------------------\n";
	SpecialMember member;
	std::cout << "Member size no.1: " << member.getSizeVec() << std::endl;
	std::cout << "-------------------------------------------------\n";
	SpecialMember member2(100);
	std::cout << "Member size no.2: " << member2.getSizeVec() << std::endl;
	std::cout << "-------------------------------------------------\n";
	SpecialMember member3(member);
	std::cout << "Member size no.3: " << member3.getSizeVec() << std::endl;
	std::cout << "-------------------------------------------------\n";
	SpecialMember member4(std::move(member3));
	std::cout << "Member size no.3: " << member3.getSizeVec() << std::endl;
	std::cout << "Member size no.4: " << member4.getSizeVec() << std::endl;
	std::cout << "-------------------------------------------------\n";
	SpecialMember member5(5);
	std::cout << "Member size no.5: " << member5.getSizeVec() << std::endl;
	member5 = member4;
	std::cout << "Member size no.4: " << member4.getSizeVec() << std::endl;
	std::cout << "Member size no.5: " << member5.getSizeVec() << std::endl;
	std::cout << "-------------------------------------------------\n";
	SpecialMember member6(5);
	std::cout << "Member size no.6: " << member6.getSizeVec() << std::endl;
	member6 = std::move(member4);
	std::cout << "Member size no.4: " << member4.getSizeVec() << std::endl;
	std::cout << "Member size no.6: " << member6.getSizeVec() << std::endl;
	std::cout << "-------------------------------------------------\n";
}
