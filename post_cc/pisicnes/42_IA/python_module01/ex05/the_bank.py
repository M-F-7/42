class Account(object):
    ID_COUNT = 1
    def __init__(self, name, **kwargs):
        self.__dict__.update(kwargs)
        self.id = self.ID_COUNT
        Account.ID_COUNT += 1
        self.name = name
        if not hasattr(self, 'value'):
            self.value = 0
        if self.value < 0:
            raise AttributeError("Attribute value cannot be negative.")
        if not isinstance(self.name, str):
            raise AttributeError("Attribute name must be a str object.")
    def transfer(self, amount):
        self.value += amount


# in the_bank.py
class Bank(object):
    """The bank"""
    def __init__(self):
        self.accounts = []

    def add(self, new_account):
        """ Add new_account in the Bank
            new_account: Account() new account to append
            @return True if success, False if an error occured
        """
        if isinstance(new_account, Account) == False:
            return False
        try:
            self.accounts.index(new_account)
            return False
        except ValueError:
            pass
        self.accounts.append(new_account)
        return True



    def transfer(self, origin:str, dest:str, amount:float):
        """" Perform the fund transfer
        @origin: str(name) of the first account
        @dest: str(name) of the destination account
        @amount: float(amount) amount to transfer
        @return True if success, False if an error occured
        """
        if isinstance(origin, str) == False:
            return False
        if isinstance(dest, str) == False:
            return False

        if (amount < 0):
            return False
        
        ori_acc = next((acc for acc in self.accounts if acc.name == origin), None)
        dest_acc = next((acc for acc in self.accounts if acc.name == dest), None)

        if ori_acc == None or dest_acc == None:
            return False
        for new_account in [ori_acc, dest_acc]:
            if len((new_account.__dir__())) % 2:
                return False
            
            is_zip_or_addr:bool = False
            is_info:int = 0
            for att in new_account.__dir__():
                if att.startswith("b"):
                    return False
                if att == "zip" or att == "addr":
                    is_zip_or_addr = True
                if att in ("name", "id", "value"):
                    if att == "name":
                        if isinstance(att, str) == False:
                            return False
                    elif att == "id":
                        if isinstance(getattr(new_account, att), int) == False:
                            return False
                    elif att == "value":
                        if isinstance(getattr(new_account, att), int) == False and isinstance(getattr(new_account, att), float) == False:
                            return False
                    is_info += 1 
            if is_zip_or_addr == False:
                return False
            if is_info != 3:
                return False
    
        if amount > ori_acc.value:
            return False
        
        if origin == dest:
            return True
        
        ori_acc.value -= amount
        dest_acc.value += amount
        return True

    def fix_account(self, name:str):
        """ fix account associated to name if corrupted
        @name: str(name) of the account
        @return True if success, False if an error occured
        """
        if isinstance(name, str) == False:
            return False
        corr_account = next((acc for acc in self.accounts if getattr(acc, "name", None) == name), None)
        if corr_account is None:
            return False
        atts = corr_account.__dir__()

        if len(atts) % 2:
            setattr(corr_account, "Length", "Even")
        for att in atts:
            if att.startswith("b") and hasattr(corr_account, att):
                delattr(corr_account, att)
        if not "zip" in atts and not "addr" in atts:
            setattr(corr_account, "zip", "00000")
        
        if not "name" in atts:
            setattr(corr_account, "name", "foo")
        else:
            if isinstance(corr_account.name, str) == False:
                try:
                    corr_account.name = str(corr_account.name)
                except Exception:
                    print("Cannot set the name attribut to a string")
                
        if not "id" in atts:
            setattr(corr_account, "id", corr_account.id)
        else:
            if isinstance(corr_account.id, int) == False:
                try:
                    corr_account.id = int(corr_account.id)
                except Exception:
                    print("Cannot set the id attribut to an int")
        if not "value" in atts:
            setattr(corr_account, "value", corr_account.value)
        else:
            if isinstance(corr_account.value, int) == False and isinstance(corr_account.value, float) == False:
                try:
                    corr_account.value = float(corr_account.value)
                except Exception:
                    print("Cannot set the value attribut to an int/float")
        return True