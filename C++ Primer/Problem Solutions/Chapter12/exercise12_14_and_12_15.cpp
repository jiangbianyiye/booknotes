#include<iostream>
#include<memory>

using namespace std;

struct destination {};
struct connection {
    destination* dst;
};

connection connect(destination* dst)
{   
    cout<<"open connection: "<<dst<<endl;
    connection con;
    con.dst = dst;
    return con;
}

void disconnect(connection c)
{
    delete c.dst;
    cout<<"delete connection: "<<c.dst<<endl;
}

void end_connection(connection *con)
{
    disconnect(*con);
}

void f(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
    cout<<"use connection: "<<p->dst<<endl;
}

void f2(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, [](connection* con){
        disconnect(*con);
    });
    cout<<"use connection: "<<p->dst<<endl;
}

int main(int argc, char const *argv[])
{   
    cout<<"12_14:"<<endl;
    destination* dst = new destination();
    f(*dst);

    cout<<"12_15:"<<endl;
    destination* dst2 = new destination();
    f2(*dst2);
    return 0;
}

/* output:
12_14:
open connection: 0x7fffe5363080
use connection: 0x7fffe5363080
delete connection: 0x7fffe5363080
12_15:
open connection: 0x7fffe5363080
use connection: 0x7fffe5363080
delete connection: 0x7fffe5363080
*/
