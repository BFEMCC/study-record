#include "RandomNumberGenerator.h"

UNINT emc::RandomNumberGenerator::CRand()
{
	srand(static_cast<UNINT>(time(NULL)));
	return rand() + static_cast<UNINT>(clock());
}

u_vector_ptr_int emc::RandomNumberGenerator::UniformDist_int(const int minRange, const int maxRange, const int quantity)
{
	assert(quantity >= 1);
	if (quantity < 1){
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	u_vector_ptr_int RandNum(new std::vector<int>);
	seed(random_device::operator()() + CRand());
	std::uniform_int_distribution<>uniformDist(minRange, maxRange);
	for (int i = 0; i < quantity; i++){
		RandNum->push_back(uniformDist(static_cast<std::mt19937&>(*this)));//生成随机整数
	}
	return RandNum;
}

u_vector_ptr_double emc::RandomNumberGenerator::UniformDist_double(const double minRange, const double maxRange, const int quantity)
{
	assert(quantity >= 1);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	u_vector_ptr_double RandNum(new std::vector<double>);
	seed(random_device::operator()() + CRand());
	std::uniform_real_distribution<> uniformDist(minRange, maxRange); //均匀分布浮点数
	for (int i = 0; i < quantity; i++) {
		RandNum->push_back(uniformDist(static_cast<std::mt19937&>(*this)));//生成随机浮点数
	}
	return RandNum;
}

u_vector_ptr_int emc::RandomNumberGenerator::NormalDist_int(const double u, const double o, const int quantity)
{
	assert(quantity >= 1);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	u_vector_ptr_int RandNum(new std::vector<int>);
	seed(random_device::operator()() + CRand());
	std::normal_distribution<> normalDist(u, o); // 浮点数正态分布
	for (int i = 0; i < quantity; i++){
		RandNum->push_back(static_cast<int>(normalDist(static_cast<std::mt19937&>(*this))));//取整数部分
	}
	return RandNum;
}

u_vector_ptr_double emc::RandomNumberGenerator::NormalDist_double(const double u, const double o, const int quantity)
{
	assert(quantity >= 1);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	u_vector_ptr_double RandNum(new std::vector<double>);
	seed(random_device::operator()() + CRand());
	std::normal_distribution<> normalDist(u, o); // 浮点数正态分布
	for (int i = 0; i < quantity; i++) {
		RandNum->push_back(normalDist(static_cast<std::mt19937&>(*this)));
	}
	return RandNum;
}

u_vector_ptr_int emc::RandomNumberGenerator::ExponentialDist_int(const double lambda, const int quantity)
{
	assert(quantity >= 1 && lambda > 0);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	else if (lambda <= 0) {
		throw emc::emcException("The parameter is less than or equal to 0!\n参数小于等于0！");
	}
	u_vector_ptr_int RandNum(new std::vector<int>);
	seed(random_device::operator()() + CRand());
	std::exponential_distribution<double> exponentialDist(lambda);
	for (int i = 0; i < quantity; i++) {
		RandNum->push_back(static_cast<int>(exponentialDist(static_cast<std::mt19937&>(*this))));
	}
	return RandNum;
}

u_vector_ptr_double emc::RandomNumberGenerator::ExponentialDist_double(const double lambda, const int quantity)
{
	assert(quantity >= 1 && lambda > 0);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	else if (lambda <= 0) {
		throw emc::emcException("The parameter is less than or equal to 0!\n参数小于等于0！");
	}
	u_vector_ptr_double RandNum(new std::vector<double>);
	seed(random_device::operator()() + CRand());
	std::exponential_distribution<double> exponentialDist(lambda);
	for (int i = 0; i < quantity; i++) {
		RandNum->push_back(exponentialDist(static_cast<std::mt19937&>(*this)));
	}
	return RandNum;
}

u_vector_ptr_int emc::RandomNumberGenerator::PoissonDist_int(const double lambda, const int quantity)
{
	assert(quantity >= 1 && lambda > 0);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	else if (lambda <= 0) {
		throw emc::emcException("The parameter is less than or equal to 0!\n参数小于等于0！");
	}
	u_vector_ptr_int RandNum(new std::vector<int>);
	seed(random_device::operator()() + CRand());
	std::poisson_distribution<int> poissonDist(lambda);
	for (int i = 0; i < quantity; i++) {
		RandNum->push_back(static_cast<int>(poissonDist(static_cast<std::mt19937&>(*this))));
	}
	return RandNum;
}

u_vector_ptr_int emc::RandomNumberGenerator::GammaDist_int(const double shape, const double scale, const int quantity)
{
	assert(quantity >= 1);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	u_vector_ptr_int RandNum(new std::vector<int>);
	seed(random_device::operator()() + CRand());
	std::gamma_distribution<double> gammaDist(shape, scale);
	for (int i = 0; i < quantity; ++i) {
		RandNum->push_back(static_cast<int>(gammaDist(static_cast<std::mt19937&>(*this))));
	}
	return RandNum;
}

u_vector_ptr_double emc::RandomNumberGenerator::GammaDist_double(const double shape, const double scale, const int quantity)
{
	assert(quantity >= 1);
	if (quantity < 1) {
		throw emc::emcException("Quantity less than 1!\n数量小于1！");
	}
	u_vector_ptr_double RandNum(new std::vector<double>);
	seed(random_device::operator()() + CRand());
	std::gamma_distribution<double> gammaDist(shape, scale);
	for (int i = 0; i < quantity; ++i) {
		RandNum->push_back(gammaDist(static_cast<std::mt19937&>(*this)));
	}
	return RandNum;
}
