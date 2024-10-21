#ifndef GROUPUSER_H
#define GROUPUSER_H

#include"user.hpp"
class GroupUser:public User{
    //群组用户，多了一个role角色信息，从User类直接继承，复用User的其他信息
    public:
    void setRole(string role){this->role=role;}
    string getRole(){return this->role;}
    private:
    string  role;
};

#endif