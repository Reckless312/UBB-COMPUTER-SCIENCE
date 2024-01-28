from random import choice


def generate_100_pseudo_random_questions():
    questions = []
    for i in range(1, 20):
        num1 = choice([-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
        num2 = choice([-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
        num3 = choice([-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
        option = choice(["largest", "smallest"])
        if option == "largest":
            question = f"{i};Which number is the {option};{num1};{num2};{num3};{max(num1, num2, num3)};easy"
            questions.append(question)
        else:
            question = f"{i};Which number is the {option};{num1};{num2};{num3};{min(num1, num2, num3)};easy"
            questions.append(question)
    # return questions
    for i in range(20, 60):
        fish1 = choice(["carp", "eel", "bass", "trout", "crab", "herring", "marlin"])
        fish2 = choice(["carp", "eel", "bass", "trout", "crab", "herring", "marlin"])
        not_fish = choice(["cow", "horse", "monkey", "tomato", "stylo", "apple"])
        question = f"{i};Which is not a fish;{fish1};{fish2};{not_fish};{not_fish};medium"
        questions.append(question)
    for i in range(60, 101):
        mission1 = choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17])
        mission2 = choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17])
        mission3 = choice([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17])
        correct_mission = choice([mission1, mission2, mission3])
        question = f"{i};Which Apollo mission did not make it to the moon;{mission1};{mission2};{mission3};{correct_mission};hard"
        questions.append(question)
    return questions
