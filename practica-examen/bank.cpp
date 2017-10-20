int main()
{
    BankSystem bs;
     
    bs.add_user(“juan”, “perez”, 19761225, “3928233LP”);
    bs.add_user(“jorge”, “cortez”, 19780114, “4007112LP”);
    bs.add_user(“maria”, “marquina”, 6655332, “5678901LP”);
     
    bs.add_account(“5678901LP”, new savings(2500));
    bs.add_account(“5678901LP”, new fixed_time(350000, fixed_time_interval::monthly));
    bs.add_account(“4007112LP”, new savings(10000));
    bs.add_account(“3928233LP”, new fixed_time(2500, fixed_time_interval::yearly));
     
    bs.iterate_accounts_by_owner(“5678901LP”, [](auto& acct)
    {
      acct.show();
    });
     
    bs.iterate_accounts_by_type<savings>([](auto& acct) { acct.show(); } );
     
    bs.iterate_accounts_by_amount_greater_than(10000, [](auto& acct) { acct.show(); });
}