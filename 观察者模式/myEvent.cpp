#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;
//�¼���Ӧ�ߣ�ί���ߣ����࣬��Ӧ����Ϊ�麯��,,��Ҫ��Ϊί�����,ֱ�ӹ��м̳�,��д��Ӧ����
class CResponsor
{
	public:
    	virtual void Changed(int value){ };
};

//�¼���������
class CEvent
{
    public:
        CEvent(int value = 0) : m_value(value){}
        void Bind(CResponsor *responsor);
        void UnBind(CResponsor *responsor);
        void ValueChanged(int value);
    private:
        vector<CResponsor *> m_eventResponsors; //�¼���Ӧ�ߣ�ί���ߣ�����ָ�����, ����ָ�����ָ������
        int m_value;
};

//����Ӧ�߰󶨵�������
void CEvent::Bind(CResponsor *responsor)
{
    bool unBind = true;
    vector<CResponsor *>::iterator it = m_eventResponsors.begin();
    vector<CResponsor *>::iterator end = m_eventResponsors.end();
    for(; it < end; it++)
    {
        if(responsor == *it)
        {
            unBind = false;
            break;
        }
    }
    if(unBind)
    {
        m_eventResponsors.push_back(responsor);
    }
    return;
}
//����Ӧ�ߴӶ�����ɾ��
void CEvent::UnBind(CResponsor *responsor)
{
    vector<CResponsor *>::iterator it = m_eventResponsors.begin();
    vector<CResponsor *>::iterator end = m_eventResponsors.end();
    for(; it < end; it++)
    {
        if(responsor == *it)
        {
            m_eventResponsors.erase(it);
            break;
        }
    }
    return;
}
//��һ����ֵ����¼�
void CEvent::ValueChanged(int value)
{
    if(value == m_value)
    {
        return;
    }
    m_value = value;
    std::cout << "CEvent��m_value�Ѿ��ı�Ϊ" << m_value << std::endl;
    if(!m_eventResponsors.empty())
    {
        vector<CResponsor *>::iterator it = m_eventResponsors.begin();
        vector<CResponsor *>::iterator end = m_eventResponsors.end();
        for(; it < end; it++)
        {
            (*it)->Changed(m_value);
        }
    }
    return;
}

//**************************************************************************//

//  �ж���, ���м̳и��� CPesponsor
class CEventResponsor : public CResponsor
{
	public:
        CEventResponsor(char *name) : m_name(name) {}
        void Listen(CEvent *trigger);
        void UnListen(CEvent *trigger);
        //  ֵ����¼�����Ӧ����
        void Changed(int value){ std::cout << m_name << ":�����Ѿ�������Ϊ��" << value << std::endl; };
    private:
        string m_name;
};
//�����¼�
void CEventResponsor::Listen(CEvent *trigger)
{
    trigger->Bind(this);
}
//ֹͣ����
void CEventResponsor::UnListen(CEvent *trigger)
{
    trigger->UnBind(this);
}


int main(void)
{
    CEvent event;
    CEventResponsor a("zhanSan"), b("liSi");

    a.Listen(&event);
    b.Listen(&event);
    event.ValueChanged(100);

    b.UnListen(&event);
    event.ValueChanged(50);

    return 0;
}
