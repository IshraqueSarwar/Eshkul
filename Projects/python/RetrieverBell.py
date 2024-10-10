import json


HYPHEN = "-"
QUIT = 'quit'
SWITCH_CONNECT = 'switch-connect'
SWITCH_ADD = 'switch-add'
PHONE_ADD = 'phone-add'
NETWORK_SAVE = 'network-save'
NETWORK_LOAD = 'network-load'
START_CALL = 'start-call'
END_CALL = 'end-call'
DISPLAY = 'display'


def connect_switchboards(switchboards, area_1, area_2):
    add_switchboard(switchboards, area_1)
    add_switchboard(switchboards, area_2)

    # adding trunk line
    switchboards[area_1][0].append(area_2)
    switchboards[area_2][0].append(area_1)
    
    # NEW: adding trunk line count
    switchboards[area_1][2].append(0)
    switchboards[area_2][2].append(0)



def add_switchboard(switchboards, area_code):
    #switchboards[areacode] = [ [trunck lines] , {dict of phone numbers connected to each other}, [each trunk line limit] ]
    if area_code not in switchboards:
        switchboards[area_code] = [ [], {}, [] ]


def add_phone(switchboards, area_code, phone_number):
    add_switchboard(switchboards, area_code)
    switchboards[area_code][1][phone_number] = None



def save_network(switchboards, file_name):
    with open(file_name, 'w') as f:
        json.dump(switchboards, f)



def load_network(file_name):
    with open(file_name, 'r') as f:
        switchboards = json.load(f)

    switchboards_converted = {}
    for area_code in switchboards:
        phone_dict = {}
        for phone in switchboards[area_code][1]:
            phone_dict[int(phone)] = None

        switchboards_converted[int(area_code)] = [switchboards[area_code][0], phone_dict, switchboards[area_code][2]]
    return switchboards_converted


def increment_trunk_connection_count(area_1, area_2, switchboards, limit):
    for i, a in enumerate(switchboards[area_1][0]):
        if a==area_2:
            if limit == switchboards[area_1][2][i]:
                return False, None
            switchboards[area_1][2][i]+=1

    for i, a in enumerate(switchboards[area_2][0]):
        if a==area_1:
            # if limit == switchboards[area_2][2][i]:
            #     return False
            switchboards[area_2][2][i]+=1

    return True, f'{area_1}-{area_2}'


def not_in_another_call(area, number, switchboards):
    if number in switchboards[area][1]:
        if switchboards[area][1][number] == None:
            return True
        return False
    else:
        return True
    return False


def is_valid_area_code(area_code, switchboards):
    if area_code in switchboards:
        return True
    return False

def add_end_call_trunk_route(end_call_trunk_routes, area_start_number, area_end_number, lines):
    if area_start_number not in end_call_trunk_routes:
        end_call_trunk_routes[area_start_number] = [lines]
        end_call_trunk_routes[area_end_number] = [lines]
    else:
        end_call_trunk_routes[area_start_number].append(lines)
        end_call_trunk_routes[area_end_number].append(lines)
        


def has_interconnection(switchboards, start_area, end_area, visited, t_limit, end_call_trunk_routes, area_start_number, area_end_number):
    if start_area == end_area:
        return True

    trunk_line_list = switchboards[start_area][0]
    for trunk_line in trunk_line_list:
        if trunk_line not in visited:
            visited.append(trunk_line)
            if trunk_line == end_area:
                rtn, l = increment_trunk_connection_count(start_area, end_area, switchboards, t_limit)
                # print(l)
                if l!= None:
                    add_end_call_trunk_route(end_call_trunk_routes, area_start_number, area_end_number, l)
                return rtn
            else:
                rt = has_interconnection(switchboards, trunk_line, end_area, visited, t_limit,end_call_trunk_routes, area_start_number, area_end_number)
                if rt:
                    rtn, l = increment_trunk_connection_count(start_area, trunk_line, switchboards, t_limit)
                    # print(l)
                    if l!= None:
                        add_end_call_trunk_route(end_call_trunk_routes, area_start_number, area_end_number, l)
                    return rtn
    
    return False
    


def start_call(switchboards, start_area, start_number, end_area, end_number, t_limit, end_call_trunk_routes):
    if is_valid_area_code(start_area, switchboards) and is_valid_area_code(end_area, switchboards)\
        and not_in_another_call(start_area, start_number, switchboards) and not_in_another_call(end_area, end_number, switchboards):
        start_area_str = str(start_area)
        start_number_str = str(start_number)
        end_area_str = str(end_area)
        end_number_str = str(end_number)

        visited = [start_area]
        area_start_number = f'{start_area_str}-{start_number_str}'
        area_end_number = f'{end_area_str}-{end_number_str}'
        is_interconnected = has_interconnection(switchboards, start_area, end_area, visited, t_limit,end_call_trunk_routes, area_start_number, area_end_number)
        
        if is_interconnected:
            switchboards[start_area][1][start_number] = f"{end_area}-{end_number}"
            switchboards[end_area][1][end_number] = f"{start_area}-{start_number}"
            print(f"{start_area_str}-{start_number_str[:3]}-{start_number_str[3:]} and {end_area_str}-{end_number_str[:3]}-{end_number_str[3:]} are now connected.")
        
        else:
            print(f"{start_area_str}-{start_number_str[:3]}-{start_number_str[3:]} and {end_area_str}-{end_number_str[:3]}-{end_number_str[3:]} were not connected.")
    else:
        print('Invalid Area code/number/in another call... Try again')
        

def remove_connections(end_call_trunk_routes, area_start_number, area_end_number, switchboards):
    for line in end_call_trunk_routes[area_end_number]:
        area_1, area_2 = line.split('-')
        area_1 = int(area_1)
        area_2 = int(area_2)
        
        for i, a in enumerate(switchboards[area_1][0]):
            if a == area_2:
                switchboards[area_1][2][i]-=1
        
        
        for i, a in enumerate(switchboards[area_2][0]):
            if a == area_1:
                switchboards[area_2][2][i]-=1


    del end_call_trunk_routes[area_start_number]
    del end_call_trunk_routes[area_end_number]


def end_call(switchboards, start_area, start_number, end_call_trunk_routes):
    if start_number not in switchboards[start_area][1]:
        return

    if switchboards[start_area][1][start_number] == None:
        print('Unable to disconnect')
        return
    else:

        end_line = switchboards[start_area][1][start_number].split('-')
        end_area = int(end_line[0])
        end_number = int(end_line[1])

        switchboards[start_area][1][start_number] = None
        switchboards[end_area][1][end_number] = None

        area_start_number = f"{start_area}-{start_number}"
        area_end_number = f"{end_area}-{end_number}"
        remove_connections(end_call_trunk_routes, area_start_number, area_end_number, switchboards)

        print('Hanging up...\nConnection Terminated.')




def display(switchboards):
    # print(switchboards)
    for area_code in switchboards:
        print(f"Switchboard with area code: {area_code}")
        print("     Trunk lines are: ")
        for trunk_line in switchboards[area_code][0]:
            print(f"        Trunk line connected to: {trunk_line}")

        print("     Local phone numbers are: ")
        for local_num in switchboards[area_code][1]:
            connected_to_number = switchboards[area_code][1][local_num]
            if  connected_to_number == None:
                print(f"        Phone with number: {local_num} is not in use.")
            else:
                print(f"        Phone with number: {local_num} is connected to {connected_to_number}")




if __name__ == '__main__':
    # switchboard = {areacode: [432, 234...], {43534: 234235}, [0, 0]}
    switchboards = {}
    end_call_trunk_routes = {}
    t_limit = int(input('Enter the limit on each trunk line: '))
    s = input('Enter command: ')
    while s.strip().lower() != QUIT:
        split_command = s.split()
        if len(split_command) == 3 and split_command[0].lower() == SWITCH_CONNECT:
            area_1 = int(split_command[1])
            area_2 = int(split_command[2])
            connect_switchboards(switchboards, area_1, area_2)

        elif len(split_command) == 2 and split_command[0].lower() == SWITCH_ADD:
            add_switchboard(switchboards, int(split_command[1]))


        elif len(split_command) == 2 and split_command[0].lower() == PHONE_ADD:
            number_parts = split_command[1].split('-')
            area_code = int(number_parts[0])
            phone_number = int(''.join(number_parts[1:]))
            add_phone(switchboards, area_code, phone_number)


        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_SAVE:
            save_network(switchboards, split_command[1])
            print('Network saved to {}.'.format(split_command[1]))


        elif len(split_command) == 2 and split_command[0].lower() == NETWORK_LOAD:
            switchboards = load_network(split_command[1])
            print('Network loaded from {}.'.format(split_command[1]))



        elif len(split_command) == 3 and split_command[0].lower() == START_CALL:
            src_number_parts = split_command[1].split(HYPHEN)
            src_area_code = int(src_number_parts[0])
            src_number = int(''.join(src_number_parts[1:]))

            dest_number_parts = split_command[2].split(HYPHEN)
            dest_area_code = int(dest_number_parts[0])
            dest_number = int(''.join(dest_number_parts[1:]))
            start_call(switchboards, src_area_code, src_number, dest_area_code, dest_number, t_limit, end_call_trunk_routes)


        elif len(split_command) == 2 and split_command[0].lower() == END_CALL:
            number_parts = split_command[1].split(HYPHEN)
            area_code = int(number_parts[0])
            number = int(''.join(number_parts[1:]))
            end_call(switchboards, area_code, number, end_call_trunk_routes)


        elif len(split_command) >= 1 and split_command[0].lower() == DISPLAY:
            display(switchboards)

        s = input('Enter command: ')


