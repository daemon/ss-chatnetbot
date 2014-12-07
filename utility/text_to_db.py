from __future__ import division
import math
import re
import sqlite3

'''
Small script to convert ss convo logs to sqlite3 sentence generator database
'''

def main():
    FILENAME = "session.log"
    conn = sqlite3.connect("conversations.sqlite")
    c = conn.cursor()
    c.execute("CREATE TABLE IF NOT EXISTS conversations (hashcode INTEGER PRIMARY KEY, name TEXT, word_a TEXT, word_b TEXT, is_starting INTEGER)")
    c.execute("CREATE TABLE IF NOT EXISTS conv_metadata (avg_line_len REAL, std_dev REAL)")
    conn.commit()

    f = open(FILENAME)
    lines = f.readlines()

    rgx = r"^\s+([^<].+?)> ([^\?].*?)$"
    index = 0
    lengths = []
    for l in lines:
        if l[0] != " ":
            continue
        match = re.match(rgx, l)
        if not match:
            continue

        name = match.group(1)
        blurb = match.group(2).decode("ascii", "ignore")

        arr_words = blurb.split(' ')
        
        starting = 1
        for i_w in range(len(arr_words) - 1):
            word_a = arr_words[i_w]
            word_b = ""
            if i_w < len(arr_words) - 1:
                word_b = arr_words[i_w + 1]
                
            c.execute("INSERT OR REPLACE INTO conversations VALUES (?,?,?,?,?)", (hash(word_a + word_b), name, word_a, word_b, starting))

            if index == 100000:
                conn.commit()
                index = 0
            starting = 0
            index += 1
        lengths.append(len(arr_words))

    average = reduce(lambda x, y: x + y, lengths) / len(lengths)
    std_dev = math.sqrt(reduce(lambda x, y: x + (y - average)**2, lengths) / len(lengths))

    c.execute("INSERT INTO conv_metadata VALUES (?,?)", (average, std_dev))
    conn.commit()
    conn.close()
        
    
main()
    
