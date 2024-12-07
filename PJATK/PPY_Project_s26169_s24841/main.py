import data_base

data_base.create()

while(True):
    try:
        print("""
        [1] - Add new Product
        [2] - Find Product
        [3] - Show all Products
        [4] - Update Product
        [5] - Delete Product
        [6] - Close
        """)
        answer = input("Select option: ")

        if answer == '1':
            parameters = input("Enter next parameters: [name, description, price, amount]\n")
            param_list = parameters.split(',')
            data_base.add_product(param_list[0], param_list[1], float(param_list[2]), int(param_list[3]))

        elif answer == '2':
            while(True):
                answer = input("Would you like to find product by id [1] or name [2]: ")
                if answer == '1':
                    parameter = int(input('Enter [ID]: '))
                    data_base.find_product(parameter)
                    break
                elif answer:
                    parameter = input('Enter [name]: ')
                    data_base.find_product(parameter)
                    break
                else:
                    print("Wrong option. Try again")
                    continue

        elif answer == '3':
            data_base.find_all()

        elif answer == '4':
            parameters = input("Enter next parameters: [id, name, description, price, amount]\n")
            param_list = parameters.split(',')
            data_base.update_product(int(param_list[0]), param_list[1], param_list[2], float(param_list[3]), int(param_list[4]))

        elif answer == '5':
            parameter = int(input('Enter [ID]: '))
            data_base.delete_product(parameter)
        elif answer == '6':
            print("Good bye!")
            break
        else:
            print("Wrong option. Try again")
            continue
    except Exception:
        print("Wrong option. Try again")
        continue