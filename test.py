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
                'security': details[3] if len(details) > 3 else 'None',  # Security Type
                'signal': f'{details[4]} {details[5]} - {details[6]}%',  # Signal Strength
                'tower': f"{details[7]}",  # Signal tower
                'type': f"{details[-2]}/{details[-1]}",  # Security Type
            })    
    return wifi_list

def connect_wifi(ssid, password):
    """Connect to a Wi-Fi network using nmcli."""
    subprocess.run(['nmcli', 'device', 'wifi', 'connect', ssid, 'password', password])

def disconnect_wifi():
    """Disconnect from the current Wi-Fi network."""
    subprocess.run(['nmcli', 'device', 'disconnect', 'wlan0'])

def get_current_wifi():
    """Get the currently connected Wi-Fi network."""
    result = subprocess.run(['nmcli', 'device', 'wifi', 'show'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8').splitlines()
    if output: 
        return output[0].split(':')[1].strip()  # SSID of the current connected Wi-Fi
    return "None"  # If no Wi-Fi is connected

def main(stdscr):
    # Setup the screen
    curses.curs_set(0)  # Hide the cursor
    stdscr.timeout(100)  # Set timeout for non-blocking input
    height, width = stdscr.getmaxyx()

    wifi_list = get_wifi_list()
    current_selection = 0
    password = ''
    connected_wifi = get_current_wifi()

    while True:
        stdscr.clear()

        # Display the Wi-Fi networks in the left column
        for idx, wifi in enumerate(wifi_list):
            display_text = f"  {wifi['ssid']} | {wifi['signal']} | {wifi['tower']} | {wifi['type']}"
            if idx == current_selection:
                stdscr.addstr(idx + 1, 2, f"> {display_text}", curses.A_REVERSE)
            else:
                stdscr.addstr(idx + 1, 2, f"  {display_text}")

        # Display the currently connected Wi-Fi in the right column
        stdscr.addstr(2, width // 2 + 2, f"Connected Wi-Fi: {connected_wifi}")

        # Display instructions
        stdscr.addstr(height - 4, 2, "Use UP/DOWN arrows to navigate, ENTER to connect, ESC to exit.")
        stdscr.addstr(height - 3, 2, "Press 'r' to reconnect or 'q' to disconnect from Wi-Fi.")

        # Refresh the screen
        stdscr.refresh()

        # Get user input
        key = stdscr.getch()

        # Handle up/down navigation
        if key == curses.KEY_UP and current_selection > 0:
            current_selection -= 1  # Navigate up
        elif key == curses.KEY_DOWN and current_selection < len(wifi_list) - 1:
            current_selection += 1  # Navigate down

        # Connect function
        elif key == 10 or key == curses.KEY_RIGHT:  # Enter key | Right arrow
            while True:
                if wifi_list[current_selection]['security'] != 'None':
                    stdscr.clear()
                    stdscr.addstr(2, 2, f"Enter password for {wifi_list[current_selection]['ssid']}: ")
                    stdscr.refresh()
                    password = stdscr.getstr().decode('utf-8')

                    # Try connecting with the password
                    try:
                        connect_wifi(wifi_list[current_selection]['ssid'], password)
                        stdscr.clear()
                        stdscr.addstr(2, 2, f"Connecting to {wifi_list[current_selection]['ssid']}...")
                        stdscr.refresh()

                        # Wait for the connection to complete before continuing
                        curses.napms(2000)  # Wait 2 seconds for connection attempt

                        connected_wifi = get_current_wifi()  # Update the current connected Wi-Fi
                        stdscr.clear()
                        stdscr.addstr(2, 2, f"Successfully connected to {wifi_list[current_selection]['ssid']}.")
                        stdscr.refresh()
                        curses.napms(1000)  # Wait for 1 second before returning to the list

                    except Exception as e:
                        stdscr.clear()
                        stdscr.addstr(2, 2, f"Failed to connect: {e}")
                        stdscr.refresh()
                        curses.napms(1000)  # Wait for 1 second to show error

                else:
                    # Connect to open network
                    connect_wifi(wifi_list[current_selection]['ssid'], '')
                    connected_wifi = get_current_wifi()  # Update the current connected Wi-Fi
                    stdscr.clear()
                    stdscr.addstr(2, 2, f"Connecting to {wifi_list[current_selection]['ssid']}...")
                    stdscr.refresh()
                    curses.napms(2000)  # Wait 2 seconds for connection attempt

                    # Update and show current connection
                    connected_wifi = get_current_wifi()  # Update the current connected Wi-Fi
                    stdscr.clear()
                    stdscr.addstr(2, 2, f"Successfully connected to {wifi_list[current_selection]['ssid']}.")
                    stdscr.refresh()

                break

        # Exit
        elif key == 27:  # ESC key
            break  # Exit the program

        # Disconnect
        elif key == ord('q'):  # q key
            disconnect_wifi()
            stdscr.clear()
            stdscr.addstr(2, 2, "Disconnected from Wi-Fi.")
            stdscr.refresh()
            curses.napms(3000)
            connected_wifi = get_current_wifi()  # Update the current connected Wi-Fi
            stdscr.getch()  # Wait for user input to continue

        # Reconnect
        elif key == ord('r'):
            subprocess.run(['nmcli', 'connection', 'up', 'last'])
            stdscr.clear()
            stdscr.addstr(2, 2, "Reconnecting to the last network...")
            stdscr.refresh()
            connected_wifi = get_current_wifi()  # Update the current connected Wi-Fi
            stdscr.getch()  # Wait for user input to continue
            curses.napms(3000)

# Initialize curses
curses.wrapper(main)
