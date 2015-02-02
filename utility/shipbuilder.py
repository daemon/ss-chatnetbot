import re
import sqlite3

def main():
    conn = sqlite3.connect('itedfm.db')
    c = conn.cursor()
    c.execute('CREATE TABLE items (id SMALLINT AUTO_INCREMENT, name TEXT NOT NULL, PRIMARY KEY(id))')
    c.execute('CREATE TABLE categories (id SMALLINT AUTO_INCREMENT, name TEXT NOT NULL, PRIMARY KEY(id))')
    c.execute('CREATE TABLE item_categories (id SMALLINT NOT NULL, category SMALLINT NOT NULL)')
    c.execute('CREATE INDEX i1 ON item_categories (id)')
    c.execute('CREATE TABLE item_costs (id SMALLINT NOT NULL, cost INT, exp INT, ships TINYINT, max SMALLINT, PRIMARY KEY(id))')
    c.execute('CREATE TABLE item_stats (id SMALLINT NOT NULL, stat_id SMALLINT, change INT)')
    c.execute('CREATE INDEX i2 ON item_stats (id)')
    c.execute('CREATE TABLE stats (id SMALLINT AUTO_INCREMENT, stat_name TEXT, max_value INT, PRIMARY KEY(id))')
    c.execute('CREATE TABLE category_constraints (id SMALLINT, max INT, PRIMARY KEY(id))')
    conn.commit()

    item_info = {}
    categories = {}
    stats = {}
    stats_max = {}
    current_item = ''
    current_values = {}
    current_values['stats'] = []
    cat_counter = 1
    id_counter = 1
    stat_counter = 1

    check_min = ["bombenergy",
        "mineenergypct",
        "cloakenergy",
        "bulletdelaypct",
        "jittertime",
        "stealthenergy",
        "bombdelaypct",
        "minedelay",
        "explodepixels",
        "multienergypct",
        "extrabombdelay",
        "minedelaypct",
        "xradarenergy",
        "multidelaypct",
        "bulletenergypct",
        "shrapdamage",
        "bulletdamage",
        "multidelay",
        "mineenergy",
        "bombdamage",
        "bombdelay",
        "bombenergypct"]
    
    cat_rgx = r'^  \| (.+?)  \s+?\|$'
    cat_rgx2 = r'^  \+------------------\+--------\+------\+-\+-------\+----------\+-----\+------\+----------------------------------\+$'
    cat_rgx3 = r'^  \| Item.+$'

    item_rgx = r'^  \+----------------------------------\+$'
    item_rgx2 = r'^  \| (.+?)  \s+?\|$'

    item_rgx3 = r'^  \| \$(.+?)\s+?\| \$(.+?)\s+?\| (.+?)\s+?\| (.+)\s+?\| (.+?)\s+?\| .+?\| (.+?)\s+?\|$'
    val_rgx = r'^  \| (.+?)\s+?\| ([\=\+\-]\d+?)\s+?\|$'
    f = open('session.log')
    lines = f.readlines()
    f.close()

    for x in range(len(lines)):
        match = re.match(item_rgx3, lines[x])
        if match:
            current_values['money_cost'] = match.group(1)
            current_values['xp_cost'] = match.group(3)            
            ships_mask = 0
            ships_str = match.group(4)
                        
            for i in range(1, 9):
                if str(i) in ships_str:
                    ships_mask = ships_mask | (2 ** (i - 1))

            current_values['ships'] = ships_mask
            current_values['max'] = int(match.group(5))
            
            types = match.group(6).split(',')
            current_values['categories'] = []
            current_values['stats'] = []
            for i in types:
                if i.strip() not in categories:
                    if i.strip() == '' or i.strip() == 'SMask' or i.strip() == '2 Mount' or i.strip() == '2 Capacity' or i.strip() == 'shrapnel' or len(i.strip()) > 2 and i.strip()[0] == '-':
                        continue
                    categories[i.strip()] = cat_counter
                    cat_counter += 1
                if i.strip() in categories:
                    current_values['categories'].append(categories[i.strip()])
            current_values['id'] = id_counter
            id_counter += 1
            continue
                
        match = re.match(cat_rgx, lines[x])
        if (match):
            tmp = re.match(cat_rgx2, lines[x + 1])
            skip = 0
            if not tmp:
                skip = 1
            tmp = re.match(cat_rgx3, lines[x + 2])
            if not tmp:
                skip = 1
            if skip != 1:
                x += 2
                current_category = match.group(1)
                continue
        match = re.match(item_rgx, lines[x])
        if (match):
            skip = 0
            tmp = re.match(item_rgx2, lines[x + 1])
            if not tmp:
                skip = 1
            if skip != 1:
                x += 1
                if (current_item != ''):
                    if 'xp_cost' in current_values:
                        item_info[current_item] = current_values
                    current_values = {}
                    current_values['categories'] = []
                    current_values['stats'] = []
                current_item = tmp.group(1)                            
                continue
        match = re.match(val_rgx, lines[x])
        if (match):
            key = match.group(1)
            val = match.group(2)
            if val[0] == '=':
                val = val[1:]
            if key not in stats:
                stats[key] = stat_counter
                if key not in check_min:
                    stats_max[stat_counter] = -1000000 #lol
                else:
                    stats_max[stat_counter] = 10000000
                stat_counter += 1

            if key not in check_min:
                stats_max[stats[key]] = max(stats_max[stats[key]], int(val))
            else:
                stats_max[stats[key]] = min(stats_max[stats[key]], int(val))
            current_values['stats'].append((stats[key], int(val)))
            continue
        
    for key in item_info.keys():        
        c.execute('INSERT INTO items(id, name) VALUES(\'%s\', \'%s\')' % (str(item_info[key]['id']), key))
    for key in categories.keys():
        c.execute('INSERT INTO categories(id, name) VALUES (\'%s\', \'%s\')' % (str(categories[key]), key))
    for key in item_info.keys():
        for cat in item_info[key]['categories']:
            c.execute('INSERT INTO item_categories(id, category) VALUES (\'%s\', \'%s\')' % (str(item_info[key]['id']), str(cat)))
    for key in item_info.keys():
        c.execute("INSERT INTO item_costs(id, cost, exp, ships, max) VALUES ('%s', '%s', '%s', '%s', '%s')" % (str(item_info[key]['id']),
                                                                                                               str(item_info[key]['money_cost']),
                                                                                                               str(item_info[key]['xp_cost']),
                                                                                                               str(item_info[key]['ships']),
                                                                                                               str(item_info[key]['max'])))
    for key in item_info.keys():
        for (k, v) in item_info[key]['stats']:
            c.execute("INSERT INTO item_stats(id, stat_id, change) VALUES ('%s', '%s', '%s')" % (str(item_info[key]['id']),
                                                                                                 str(k),
                                                                                                 str(v)))
    
    for key in stats:
        c.execute("INSERT INTO stats(id, stat_name, max_value) VALUES ('%s', '%s', '%s')" % (str(stats[key]),
                                                                                             key,
                                                                                             stats_max[stats[key]]))
    conn.commit()
    conn.close()   
    
main()
