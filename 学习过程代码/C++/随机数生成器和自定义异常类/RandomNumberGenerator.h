/*
 * @file       RandomNumberGenerator
 * @brief      �����������
 * @author     EMC��
 * @version    1.2
 * @date       2023/08/01
*/
#define IF_IGNORE 0
#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_
#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <cassert>
#include <cstdlib>
#include <ctime> 
#include "emcException.h"
#if IF_IGNORE
#include <time.h> 
#include <cmath>
#endif
#
using u_vector_ptr_int = std::unique_ptr<std::vector<int>>;
using u_vector_ptr_double = std::unique_ptr<std::vector<double>>;
using UNINT = unsigned int;
#endif

//using std::vector;
//using std::unique_ptr;                  //��ռ����ָ��
//using std::random_device;               //�������������
//using std::uniform_int_distribution;    //���ȷֲ�����������������ͣ�
//using std::mt19937;                     //���������֮һ
//using std::uniform_real_distribution;   //���ȷֲ�����������������㣩
//using std::normal_distribution;         //��̬�ֲ�����������������㣩
//using std::exponential_distribution;    //ָ���ֲ�����������������㣩
//using std::poisson_distribution;        //���ɷֲ�����������������㣩
//using std::gamma_distribution;          //٤��ֲ�����������������㣩

namespace emc
{
    class RandomNumberGenerator :
        protected std::random_device, protected std::mt19937
    {
    public:
        RandomNumberGenerator() = default;
        RandomNumberGenerator(const RandomNumberGenerator&) = delete;               //���ÿ�������
        RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;    //���ÿ�����ֵ�����
        RandomNumberGenerator(RandomNumberGenerator&& other) = delete;              //�����ƶ�����
        RandomNumberGenerator& operator=(RandomNumberGenerator&& other) = delete;   //�����ƶ���ֵ�����
        ~RandomNumberGenerator() = default;

    protected:
        UNINT CRand();

    public:
        /*
        * @brief    ���ȷֲ�_����
        * @param    ��Сֵ
        * @param    ���ֵ
        * @param    ����
        * @return   ����ָ������vector<int>
        */
        u_vector_ptr_int UniformDist_int(const int minRange, const int maxRange, const int quantity = 1);

        /*
        * @brief    ���ȷֲ�_������
        * @param    ��Сֵ
        * @param    ���ֵ
        * @param    ����
        * @return   ����ָ������vector<double>
        */
        u_vector_ptr_double UniformDist_double(const double minRange, const double maxRange, const int quantity = 1);

        /*
        * @brief    ��̬�ֲ�_����
        * @param    ��ֵ
        * @param    ��׼��
        * @param    ����
        * @return   ����ָ������vector<int>
        */
        u_vector_ptr_int NormalDist_int(const double u, const double o, const int quantity = 1);

        /*
        * @brief    ��̬�ֲ�_������
        * @param    ��ֵ
        * @param    ��׼��
        * @param    ����
        * @return   ����ָ������vector<double>
        */
        u_vector_ptr_double NormalDist_double(const double u, const double o, const int quantity = 1);

        /*
        * @brief    ָ���ֲ�_����
        * @param    �˲�������ʵ����
        * @param    ����
        * @return   ����ָ������vector<int>
        */
        u_vector_ptr_int ExponentialDist_int(const double lambda, const int quantity = 1);

        /*
        * @brief    ָ���ֲ�_������
        * @param    �˲�������ʵ����
        * @param    ����
        * @return   ����ָ������vector<double>
        */
        u_vector_ptr_double ExponentialDist_double(const double lambda, const int quantity = 1);

        /*
        * @brief    ���ɷֲ�_����
        * @param    �˲�������ʵ����
        * @param    ����
        * @return   ����ָ������vector<int>
        */
        u_vector_ptr_int PoissonDist_int(const double lambda, const int quantity = 1);

#if IF_IGNORE /*���㲴�ɷֲ�������*/
        /*
        * @brief    ���ɷֲ�_������
        * @param    �˲�������ʵ����
        * @param    ����
        * @return   ����ָ������vector<double>
        */
        u_vector_ptr_double PoissonDist_double(const double lambda, const int quantity = 1);
#endif

        /*
        * @brief    ٤��ֲ�_����
        * @param    ��״����
        * @param    �߶Ȳ���
        * @param    ����
        * @return   ����ָ������vector<int>
        */
        u_vector_ptr_int GammaDist_int(const double shape, const double scale, const int quantity = 1);

        /*
        * @brief    ٤��ֲ�_������
        * @param    ��״����
        * @param    �߶Ȳ���
        * @param    ����
        * @return   ����ָ������vector<double>
        */
        u_vector_ptr_double GammaDist_double(const double shape, const double scale, const int quantity = 1);
    };

    using RNG = RandomNumberGenerator;
}

