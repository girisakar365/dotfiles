import curses
import subprocess

def get_wifi_list():
    """Get a list of available Wi-Fi networks."""
    wifi_list = []
    result = subprocess.run(['nmcli', 'device', 'wifi', 'list'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8').splitlines()[1:]  # Skip the first line (headers)
    for line in output:
        details = line.split()
        if details:
            wifi_list.append({
                'ssid': details[1],  # SSID
                'signal': details[2],  # Signal Strength
                'security': details[3] if len(details) > 3 else 'None'  # Security Type
            })
    return wifi_list

def connect_wifi(ssid, password):
    """Connect to a Wi-Fi network using nmcli."""
    subprocess.run(['nmcli', 'device', 'wifi', 'connect', ssid, 'password', password])

def disconnect_wifi():
    """Disconnect from the current Wi-Fi network."""
    subprocess.run(['nmcli', 'device', 'disconnect', 'wlan0'])

def main(stdscr):
    # Setup the screen
    curses.curs_set(0)  # Hide the cursor
    stdscr.timeout(100)  # Set timeout for non-blocking input
    height, width = stdscr.getmaxyx()

    wifi_list = get_wifi_list()
    current_selection = 0
    password = ''

    while True:
        stdscr.clear()

        # Display the list of Wi-Fi networks
        for idx, wifi in enumerate(wifi_list):
            # Ensure the line fits within terminal width
            display_text = f"  {wifi['ssid']} ({wifi['signal']}%) - {wifi['security']}"
            if len(display_text) > width - 4:  # Ensure text doesn't exceed terminal width
                display_text = display_text[:width - 4] + '...'

            if idx == current_selection:
                stdscr.addstr(idx + 1, 2, f"> {display_text}", curses.A_REVERSE)
            else:
                stdscr.addstr(idx + 1, 2, f"  {display_text}")

        # Display instructions
        stdscr.addstr(height - 4, 2, "Use UP/DOWN arrows to navigate, ENTER to connect, ESC to exit.")
        stdscr.addstr(height - 3, 2, "Press 'r' to reconnect or 'q' to disconnect from Wi-Fi.")

        # Refresh the screen
        stdscr.refresh()

        # Get user input
        key = stdscr.getch()

        if key == curses.KEY_UP and current_selection > 0:
            current_selection -= 1  # Navigate up
        elif key == curses.KEY_DOWN and current_selection < len(wifi_list) - 1:
            current_selection += 1  # Navigate down
        elif key == 10:  # Enter key
            # Prompt for password if needed
            if wifi_list[current_selection]['security'] != 'None':
                stdscr.clear()
                stdscr.addstr(2, 2, f"Enter password for {wifi_list[current_selection]['ssid']}: ")
                stdscr.refresh()
                password = stdscr.getstr().decode('utf-8')

            # Connect to the selected Wi-Fi network
            connect_wifi(wifi_list[current_selection]['ssid'], password)
            stdscr.clear()
            stdscr.addstr(2, 2, f"Connecting to {wifi_list[current_selection]['ssid']}...")
            stdscr.refresh()
            stdscr.getch()  # Wait for user input to continue
        elif key == 27:  # ESC key
            break  # Exit the program
        elif key == ord('q'):
            # Disconnect from the current Wi-Fi network
            disconnect_wifi()
            stdscr.clear()
            stdscr.addstr(2, 2, "Disconnected from Wi-Fi.")
            stdscr.refresh()
            stdscr.getch()  # Wait for user input to continue
        elif key == ord('r'):
            # Reconnect to the previously connected Wi-Fi
            subprocess.run(['nmcli', 'connection', 'up', 'last'])
            stdscr.clear()
            stdscr.addstr(2, 2, "Reconnecting to the last network...")
            stdscr.refresh()
            stdscr.getch()  # Wait for user input to continue

# Initialize curses
curses.wrapper(main)
