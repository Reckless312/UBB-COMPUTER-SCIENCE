import sys
import pygame
from Game.Game import Game
from GameErrors.Errors import GameError


class GUI:
    pygame.init()
    pygame.display.set_caption("CONNECT FOUR")

    def __init__(self):
        self.__width = 639
        self.__height = 653
        self.__screen = pygame.display.set_mode((self.__width, self.__height))
        self.__background_color = (28, 170, 156)
        self.__game_image = pygame.image.load("Icon.png")
        self.__background_picture = pygame.image.load("Board.png").convert_alpha()
        self.__background_picture_rectangle = self.__background_picture.get_rect(topleft=(0, 0))
        self.__distance_between_circles = 87
        self.__game_active = True
        self.__player_move = True
        self.__game = Game()
        self.__font = pygame.font.Font("Pixeltype.ttf", 50)
        self.__slow_time = True

    def set_color(self):
        self.__screen.fill(self.__background_color)

    def set_image(self):
        pygame.display.set_icon(self.__game_image)

    def get_command_and_rectangle(self, message: str, coordinates: tuple):
        command = self.__font.render(message, False, "Black")
        return command, command.get_rect(midbottom=coordinates)

    def draw_move(self, column, surface, color: str):
        column_position, row_position, radius = 580 - (self.__distance_between_circles * (6 - column)), 495, 31
        for i in range(4, -2, -1):
            if self.__game.get_board.validator[column] == i:
                pygame.draw.circle(surface, color, (column_position, row_position), radius)
                return
            row_position -= self.__distance_between_circles
        raise GameError

    def start_pygame(self):
        self.set_color()
        self.set_image()
        player_win_command, player_win_command_rectangle = self.get_command_and_rectangle("PLAYER WON!", (319, 643))
        computer_win_command, computer_win_command_rectangle = self.get_command_and_rectangle("COMPUTER WON!", (319, 643))
        game_draw_command, game_draw_command_rectangle = self.get_command_and_rectangle("DRAW!", (319, 643))
        restart_command, restart_command_rectangle = self.get_command_and_rectangle("Press Space To Restart", (319, 623))
        title_menu, title_menu_rectangle = self.get_command_and_rectangle("Welcome To Connect Four", (319, 20))
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if self.__game_active is True:
                    if event.type == pygame.KEYDOWN and self.__player_move is True:
                        pressed_key, first_column, last_column = pygame.key.name(event.key), 0, 6
                        try:
                            pressed_key = int(pressed_key)
                            if first_column <= pressed_key <= last_column:
                                self.__game.player_move(pressed_key)
                                self.draw_move(pressed_key, self.__background_picture, "Red")
                                self.__player_move = not self.__player_move
                                if self.__game.get_board.final_state() == 1:
                                    self.__screen.blit(player_win_command, player_win_command_rectangle)
                                    self.__game_active = False
                        except (ValueError, GameError):
                            continue
                        if self.__game.get_board.is_board_full():
                            self.__screen.blit(game_draw_command, game_draw_command_rectangle)
                            self.__game_active = False
                    if self.__player_move is False and self.__game_active is True:
                        validators = []
                        for validator in self.__game.get_board.validator:
                            validators.append(validator)
                        self.__game.computer_move()
                        column = 0
                        for validator in self.__game.get_board.validator:
                            if validator != validators[column]:
                                break
                            column += 1
                        self.draw_move(column, self.__background_picture, "Yellow")
                        self.__player_move = not self.__player_move
                        if self.__game.get_board.final_state() == -1:
                            self.__screen.blit(computer_win_command, computer_win_command_rectangle)
                            self.__game_active = False
                        if self.__game.get_board.is_board_full():
                            self.__screen.blit(game_draw_command, game_draw_command_rectangle)
                            self.__game_active = False
                    self.__screen.blit(self.__background_picture, self.__background_picture_rectangle)
                    pygame.display.update()

                    if self.__game_active is False:
                        pygame.time.delay(2000)
                        pygame.quit()
                        sys.exit()
