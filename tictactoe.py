import itertools


winning_lines = [
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  # Horizontal
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  # Vertical
        {0, 4, 8}, {2, 4, 6}              # Diagonal
    ]


def game_repr(state):
    board = """┏━━━┳━━━┳━━━┓
┃ x ┃ x ┃ x ┃
┣━━━╋━━━╋━━━┫
┃ x ┃ x ┃ x ┃
┣━━━╋━━━╋━━━┫
┃ x ┃ x ┃ x ┃
┗━━━┻━━━┻━━━┛"""
    board_pieces = board.split('x')
    acc = board_pieces[0]
    for i in range(9):
        acc += state[i] + board_pieces[i + 1]
    return acc


def get_input_pos(current_state, sign, target, question):
    while True:
        done = True
        try:
            place = int(input(f"Spelare {sign}, vilken ruta vill du flytta ditt {sign} {question} ")) - 1
            if not (0 <= place < 9 and current_state[place] == target):
                raise ValueError
        except ValueError:
            done = False
            print("platsen du angav var inte giltig, var vänlig försök igen.")
        finally:
            if done:
                return place


def main():
    current_state = [' '] * 9

    print("Såhär ser din spelplan ut: ")
    print(game_repr("123456789"))
    print("Nu börjar det, håll i er! :)")

    sign = 'O'
    for i in itertools.count():
        sign = 'X' if sign == 'O' else 'O'

        if i < 6:
            move_to = get_input_pos(current_state, sign, ' ', "till? Skriv ett tal mellan 1-9:")
        else:
            move_from = get_input_pos(current_state, sign, sign, "från?")
            move_to = get_input_pos(current_state, sign, ' ', "till?")
            current_state[move_from] = ' '

        current_state[move_to] = sign
        print(game_repr("".join(current_state)))

        owned_positions = filter(lambda pos: current_state[pos] == sign, range(9))
        if any(map(lambda line: line.issubset(owned_positions), winning_lines)):
            print(f"{sign} vann! Grattis!")
            break


main()
