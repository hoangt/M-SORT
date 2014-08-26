#!/usr/bin/tclsh

# Sort network: stage 0
for {set i 0} {$i < 64} {incr i 4} {
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[$i\], " "vr_data\[[expr $i+1]\]);" "sort_up(vr_data\[[expr $i+2]\], " "vr_data\[[expr $i+3]\]);"]
}
puts "\n\n"

#Sort network: stage 1
for {set i 0} {$i < 64} {incr i 8} {
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[$i\], " "vr_data\[[expr $i+2]\]);" "sort_dw(vr_data\[[expr $i+1]\], " "vr_data\[[expr $i+3]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+4]\], " "vr_data\[[expr $i+6]\]);" "sort_up(vr_data\[[expr $i+5]\], " "vr_data\[[expr $i+7]\]);"]
}
puts "\n"
for {set i 0} {$i < 64} {incr i 8} {
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[$i\], " "vr_data\[[expr $i+1]\]);" "sort_dw(vr_data\[[expr $i+2]\], " "vr_data\[[expr $i+3]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+4]\], " "vr_data\[[expr $i+5]\]);" "sort_up(vr_data\[[expr $i+6]\], " "vr_data\[[expr $i+7]\]);"]
}
puts "\n\n"


#Sort network: stage 2
for {set i 0} {$i < 64} {incr i 16} {
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[$i\], " "vr_data\[[expr $i+4]\]);" "sort_dw(vr_data\[[expr $i+1]\], " "vr_data\[[expr $i+5]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[[expr $i+2]\], " "vr_data\[[expr $i+6]\]);" "sort_dw(vr_data\[[expr $i+3]\], " "vr_data\[[expr $i+7]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+8]\], " "vr_data\[[expr $i+12]\]);" "sort_up(vr_data\[[expr $i+9]\], " "vr_data\[[expr $i+13]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+10]\], " "vr_data\[[expr $i+14]\]);" "sort_up(vr_data\[[expr $i+11]\], " "vr_data\[[expr $i+15]\]);"]
}
puts "\n"

for {set i 0} {$i < 64} {incr i 16} {
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[$i\], " "vr_data\[[expr $i+2]\]);" "sort_dw(vr_data\[[expr $i+1]\], " "vr_data\[[expr $i+3]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[[expr $i+4]\], " "vr_data\[[expr $i+6]\]);" "sort_dw(vr_data\[[expr $i+5]\], " "vr_data\[[expr $i+7]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+8]\], " "vr_data\[[expr $i+10]\]);" "sort_up(vr_data\[[expr $i+9]\], " "vr_data\[[expr $i+11]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+12]\], " "vr_data\[[expr $i+14]\]);" "sort_up(vr_data\[[expr $i+13]\], " "vr_data\[[expr $i+15]\]);"]
}

puts "\n"
for {set i 0} {$i < 64} {incr i 16} {
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[$i\], " "vr_data\[[expr $i+1]\]);" "sort_dw(vr_data\[[expr $i+2]\], " "vr_data\[[expr $i+3]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_dw(vr_data\[[expr $i+4]\], " "vr_data\[[expr $i+5]\]);" "sort_dw(vr_data\[[expr $i+6]\], " "vr_data\[[expr $i+7]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+8]\], " "vr_data\[[expr $i+9]\]);" "sort_up(vr_data\[[expr $i+10]\], " "vr_data\[[expr $i+11]\]);"]
	puts [format "%7s%-21s%-16s%-21s%-16s" "" "sort_up(vr_data\[[expr $i+12]\], " "vr_data\[[expr $i+13]\]);" "sort_up(vr_data\[[expr $i+14]\], " "vr_data\[[expr $i+15]\]);"]
}

puts "\n"
