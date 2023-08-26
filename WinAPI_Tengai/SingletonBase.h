#pragma once

template <class T>
class SingletonBase
{
protected:
	// �̱��� �ν��Ͻ�
	static T* singleTon;

	SingletonBase() {}
	~SingletonBase() {}

public:
	// �̱��� ��������
	static T* getSingleton(void);

	// �̱��� �޸𸮿��� ����
	void releaseSingleton(void);
};

// �̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::singleTon = 0;

// �̱��� ��������
template <typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleTon) singleTon = new T;

	return singleTon;
}

// �̱��� �޸� ����
template <typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	// �̱����� �ִٸ� �޸𸮿��� ����
	if (singleTon)
	{
		delete(singleTon);
		singleTon = 0;
	}
}