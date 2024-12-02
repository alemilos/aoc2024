def is_safe(values):
    increasing = None 
    last = values[0]

    for curr in values[1:]:
        diff = abs(curr - last)
        if not (diff >=1 and diff <=3):
            return False

        if increasing == None:
            if curr > last: increasing= True
            elif curr < last: increasing= False
        elif increasing== True:
            if curr < last: return False
        elif increasing== False:
            if curr > last: return False 

        last = curr

    return True
        

def is_safe_with_problem_dampener(values):
    for i in range(len(values)):
        if is_safe(values[:i] + values[i+1:]): 
            print(f"{values} wasn't safe. {values[:i] + values[i+1:]} is.") 
            return True
    
    return False
    


def puzzle_two():
    safes = 0
    with open("./input.txt", "r") as file:
        lines = file.readlines()
        for line in lines:
            values = list(map(lambda x: int(x), line.split()))
            if is_safe(values) or is_safe_with_problem_dampener(values):
                safes+=1

    return safes 

print(puzzle_two())