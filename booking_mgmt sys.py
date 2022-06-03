def file_read(filename):
    file_dict = {}
    file_lst = []
    with open(filename, 'r') as rf:
        for line in rf:
            line.strip('\n')
            ln = line.split()
            file_dict['day'] = ln[0]
            file_dict['event'] = ln[1]
            file_dict['st'] = ln[2]
            file_dict['et'] = ln[3]
            file_lst.append(file_dict)
            file_dict = {}
        return file_lst

meeting_cachelst = []
metsession = {}
command = ''

filename = input("File to initialize the system:\n")

while command != "Exit":
    command = input("Command:\n")
    if command == "ListCourses":
        count = 0
        day = input("Day of week:\n")
        for session in file_read(filename):
            if session['day'] == day:
                count+=1
            else:
                pass
        if count == 0:
            print("You have no session on", day + '.')
    
        else:
            print("You have", count, "session(s) on", day, end = ':\n')
            for session in file_read(filename):
                if session['day'] == day:
                    print(session['event'], '- from', session['st'], 'to', session['et'] + '.')
                else:
                    continue
                
    elif command == "TotalCourses":
        setcour = set()
        for session in file_read(filename):
            setcour.add(session['event'])        
        print("You have", len(setcour), "course(s) in your weekly timetable.")
        
    elif command == "AddMeeting":
        day = input("Day of week:\n")
        stime = input("Start time:\n")
        etime = input("End time:\n")
        metname = input("Name:\n")
        avaliable = True
        schedule = file_read(filename) + meeting_cachelst
        for session in schedule:
            if session['day'] == day:
                st1 = int(stime.replace(':', ''))
                et1 = int(etime.replace(':', ''))
                st = int(session.get('st').replace(':', ''))
                et = int(session.get('et').replace(':', ''))
                if (st < st1 < et) or (st < et1 < et):
                    avaliable = False
                    break
                else:
                    continue
        
        if avaliable == True:
            metsession['day'] = day
            metsession['event'] = metname
            metsession['st'] = stime
            metsession['et'] = etime
            meeting_cachelst.append(metsession)
            metsession = {}
            print("Meeting", '(' + stime, '-', etime + ') for', metname, 'on', day, 'added to your weekly timetable.')
        else:
            print("Timeslot", '(' + stime, '-', etime + ') clashes with other session(s) on', day + '.')

    elif command == "DelMeeting":
        day = input("Day of week:\n")
        stime = input("Start time of the meeting:\n")
        ind = 9999999
        for session in meeting_cachelst:
            if session['day'] == day and session['st'] == stime:
                ind = meeting_cachelst.index(session)
            else:
                continue
        if ind != 9999999:
            print("Meeting", '(' + meeting_cachelst[ind]['st'], '-', meeting_cachelst[ind]['et'] + ') for', meeting_cachelst[ind]['event'], 'on', meeting_cachelst[ind]['day'], 'removed from your weekly timetable.')
            meeting_cachelst.pop(ind)
        else:
            print("Meeting not found.")                 
        

    elif command == "CheckTime":
        day = input("Day of week:\n")
        time = input("Time:\n")
        timelst = file_read(filename) + meeting_cachelst
        ind = 999999
        for session in timelst:
            if session['day'] == day and (int(session['st'].replace(':', '')) <= int(time.replace(':', '')) < int(session['et'].replace(':', ''))):
                ind = int(timelst.index(session))
            else:
                continue
        if ind != 999999:
            print("Time", '('+ time + ') clashes with', timelst[ind]['event'], '(' + timelst[ind]['st'], '-', timelst[ind]['et'] + ')', 'on', timelst[ind]['day'] + '.')
        else:
            print("You are free at", time, 'on', day + '.')
        
else:
    print("Bye")





