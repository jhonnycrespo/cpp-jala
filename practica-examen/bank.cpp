#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct account
{
    int amount;

    account(int amount): amount(amount) {}

    // void show() const
    // {
    //     cout << "amount: " << amount << endl;
    // }
};

struct user
{
    string name;
    string lastname;
    int code;
    string ci;

    // vector<account*> accounts;

    user() {}

    user(string name, string lastname, int code, string ci): name(name), lastname(lastname), code(code), ci{ci} {}
};

// struct user_comparator
// {
//     bool operator()(const user& a, const user& b) const
//     {
//         return a.ci < b.ci;
//     }
// };

struct BankSystem
{
    map<string, user> map_user;

    void add_user(string name, string lastname, int code, string ci)
    {
        map_user[ci] = user {name, lastname, code, ci};
    }

    void add_account(string ci, account* ac)
    {
        // auto i = map_user.find(ci);

        // if (i == map_user.end())
        //     cout << "Not Found!\n";
        // else
        // {
        //     cout << "Found!\n";
        //     i->second.accounts.push_back(ac);
        // }
    }

    template <typename T>
    void iterate_accounts_by_owner(const string ci, T lambda)
    {
        // auto i = map_user.find(ci);

        // if (i == map_user.end())
        //     cout << "User Not Found!\n";
        // else
        // {
        //     auto person = i->second;

        //     for (auto p: person.accounts)
        //     {
        //         lambda(*p);
        //     }
        // }
    }

    template <typename A, typename L>
    void iterate_accounts_by_type(L lambda)
    {
        // for (auto const& x: map_user)
        // {
        //     for (auto const& ac: x.second.accounts)
        //     {
        //         lambda(A);
        //     }
        // }
    }

    template <typename T>
    void iterate_accounts_by_amount_greater_than(int val, T lambda)
    {

    }
};

struct savings: public account
{
    savings(int amount): account(amount) {}

//     show() const
//     {
//         cout << "showing savings\n";
//     }
};

enum fixed_time_interval
{
    monthly,
    yearly
};

struct fixed_time: public account
{
    fixed_time_interval fti;

    fixed_time(int amount, fixed_time_interval fti): account(amount), fti(fti) {}
};

int main()
{
    BankSystem bs;
    
    bs.add_user("juan", "perez", 19761225, "3928233LP");
    bs.add_user("jorge", "cortez", 19780114, "4007112LP");
    bs.add_user("maria", "marquina", 6655332, "5678901LP");
     
    bs.add_account("5678901LP", new savings(2500));
    bs.add_account("5678901LP", new fixed_time(350000, fixed_time_interval::monthly));
    bs.add_account("4007112LP", new savings(10000));
    bs.add_account("3928233LP", new fixed_time(2500, fixed_time_interval::yearly));
     
    bs.iterate_accounts_by_owner("5678901LP", [](auto& acct) {
        acct.show();
    });
     
    bs.iterate_accounts_by_type<savings>([](auto& acct) { acct.show(); } );
     
    bs.iterate_accounts_by_amount_greater_than(10000, [](auto& acct) { acct.show(); });
}