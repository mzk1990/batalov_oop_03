#pragma once
#include < iostream >
#include "Container.h"
#include < string >
#include< sstream > 
template< class T > 
struct numcopies
{
    static size_t copies(  ) { return sm_counter(  ); }
protected:
    ~numcopies() { --sm_counter(); }
    numcopies() { ++sm_counter(); }
private:
    static size_t & sm_counter(  ) { static size_t c = 0; return c; } 
};


class Object : public numcopies<  Object > {
public:
    virtual ~Object(  ) {}
    virtual std::string to_string(  ) const = 0;
};

class Named :virtual public Object {
public:
    Named( std::string & s  ):m_name( s ) {};
    virtual std::string to_string(  ) const = 0;
protected:
    std::string m_name;
};

class Task : virtual public Object { 
public:
    virtual std::string to_string(  ) const = 0;
    virtual int do_Smth(  ) = 0;
};

class BinaryTask : public Named, public Task {
public:
    BinaryTask( std::string name, double x, double y ) : Named( name ), m_x( x ), m_y( y ) {};
    std::string to_string(  ) const override {
        if ( m_flag ) {
            return "operation " + Named::m_name + " is not performed";
        }
        std::stringstream stream;
        stream <<  m_res;
        std::string str = stream.str(  );
        return "operation " + Named::m_name + " has the m_result equal to " + str;
    }
    int do_Smth(  ) {
        if ( m_flag ) {
            m_flag = false;
            if ( Named::m_name == "plus" ) {
                m_res = m_x + m_y;
            }
            if ( Named::m_name == "minus" ) {
                m_res = m_x - m_y;
            }
            if ( Named::m_name == "multiply" ) {
                m_res = m_x * m_y;
            }
            if ( Named::m_name == "div" ) {
                try
                {
                    if ( m_y == 0 ) throw std::exception( "Деление на 0" );
                    m_res = m_x / m_y;
                }
                catch ( std::exception& e )
                {
                    std::cout <<  e.what(  );
                }
            }
        }
        return 0;
    }
private:
    double m_x, m_y;
    double m_res = 0;
    bool m_flag = true;
};

class AddTask : public Task {
public:
    std::string to_string(  ) const override {
        return "AddTask";
    }

    int do_Smth( Container< Object&> &c, Object & t ) {
        c.push_back( t );
        return 0;
    }
};

class CounterTask : public Task {
public:
    std::string to_string(  ) const override {
        return "CounterTask";
    }

    int do_Smth( Container< Object>& c ) {
        return c.get_count(  );
    }
};

class CounterNammedTask : public Task {
public:
    std::string to_string(  ) const override {
        if ( m_flag ) {
            return "CounterTask is not performed";
        }
        std::stringstream stream;
        stream <<  m_res;
        std::string str = stream.str(  );
        return "operation CounterTask has the m_result equal to" + str;
    }

    int do_Smth( Container< Object&>& c ) {
        if ( m_flag ) {
            m_flag = false;
            m_res = c.get_count(  ); //не планирую добавлять задачи без результата
        }
        return 0;
    }
private:
    bool m_flag = true;
    int m_res = 0;
};

class CleanerTask : public Task {
    std::string to_string(  ) const override {
        return "CleanerTask";
    }

    int do_Smth( Container< Object&>& c ) {
        c.clear(  );
        return 0;
    }
};

class CounterTaskObject : public Task {
public:
    std::string to_string(  ) const override {
        std::stringstream stream;
        stream <<  Object::copies(  );
        std::string str = stream.str(  );
        return "at the moment there are " + str + " Object";
    }

    int do_Smth(  ) {
        return 0;
    }
};