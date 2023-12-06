from src.repository import Repository
"""
Doesn't connect with any other package
"""


class MemoryRepository(Repository):
    """
    This Repository doesn't need anything else than the initial functions
    found in "Repository" / via subclass.
    """
    def __init__(self):
        """
        Backward compatibility
        """
        super().__init__()
