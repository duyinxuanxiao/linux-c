#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;
//事件响应者（委托者）父类，响应动作为虚函数,,需要作为委托类的,直接公有继承,重写响应函数
class CResponsor
{
	public:
    	virtual void Changed(int value){ };
};

//事件发出者类
class CEvent
{
    public:
        CEvent(int value = 0) : m_value(value){}
        void Bind(CResponsor *responsor);
        void UnBind(CResponsor *responsor);
        void ValueChanged(int value);
    private:
        vector<CResponsor *> m_eventResponsors; //事件响应者（委托者）父类指针队列, 父类指针可以指向子类
        int m_value;
};

//把响应者绑定到队列中
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
//把响应者从队列中删除
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
//逐一触发值变更事件
void CEvent::ValueChanged(int value)
{
    if(value == m_value)
    {
        return;
    }
    m_value = value;
    std::cout << "CEvent的m_value已经改变为" << m_value << std::endl;
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

//  行动者, 公有继承父类 CPesponsor
class CEventResponsor : public CResponsor
{
	public:
        CEventResponsor(char *name) : m_name(name) {}
        void Listen(CEvent *trigger);
        void UnListen(CEvent *trigger);
        //  值变更事件的响应函数
        void Changed(int value){ std::cout << m_name << ":报告已经被更改为：" << value << std::endl; };
    private:
        string m_name;
};
//侦听事件
void CEventResponsor::Listen(CEvent *trigger)
{
    trigger->Bind(this);
}
//停止侦听
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
