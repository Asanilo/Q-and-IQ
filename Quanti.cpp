#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

//量化函数ParaQuanti，把每个元素放大10000倍后，保存为无符号短整数（unsigned short）
void ParaQuanti(float* arr, unsigned short* quantizedArr, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        quantizedArr[i] = static_cast<unsigned short>(arr[i] * 10000);
    }
}
//逆量化函数InverseQuanti，将整数缩小10000倍后，保存为浮点数（float）
void InverseQuanti(unsigned short* quantizedArr, float* arr, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        arr[i] = static_cast<float>(quantizedArr[i]) / 10000;
    }
}
//均方根误差函数,差的平方和除以数量再开方
float CalculateRMSE(float* arr1, float* arr2, int size) 
{
    float sum = 0;
    for (int i = 0; i < size; i++) {
        float diff = arr1[i] - arr2[i];
        sum += (diff * diff);
    }
    return sqrt(sum / size);
}

int main() 
{
    int size;
    cout << "请输入数组的长度: ";
    cin >> size;//输入数组长度

    float* originalArr = new float[size];
    unsigned short* quantizedArr = new unsigned short[size];
    float* inverseQuantizedArr = new float[size];

    // 初始化随机数生成器
    srand(int(time(0)));

    // 生成0到1之间的随机数
    for (int i = 0; i < size; i++) 
    {
        originalArr[i] = float(rand()) / RAND_MAX;
    }

    ParaQuanti(originalArr, quantizedArr, size);//量化数组
    InverseQuanti(quantizedArr, inverseQuantizedArr, size);//逆量化数组

    cout << "原数组为: ";
    for (int i = 0; i < size; i++) 
    {
        cout << originalArr[i] << " ";
    }
    cout << endl;

    cout << "量化数组为: ";
    for (int i = 0; i < size; i++)
    {
        cout << quantizedArr[i] << " ";
    }
    cout << endl;

    cout << "逆量化数组为: ";
    for (int i = 0; i < size; i++) 
{
        cout << inverseQuantizedArr[i] << " ";
    }
    cout << endl;

    // 计算并打印均方根误差
    float rmse = CalculateRMSE(originalArr, inverseQuantizedArr, size);
    cout << "均方根误差为: " << rmse << endl;

    delete[] originalArr;
    delete[] quantizedArr;
    delete[] inverseQuantizedArr;

    return 0;
}
