
const months = [
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
];
const weekdays = ["Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday", "Friday", "Saturday"]


function monthName(number) {
    return months[number - 1];
}

function formatDateInClientTimeZone(generalDate) {
    let date = new Date(generalDate);
    date.setMinutes(date.getMinutes() - date.getTimezoneOffset())
    const clientTimeZone = Intl.DateTimeFormat().resolvedOptions().timeZone;
    const options = {
        timeZone: clientTimeZone,
    }
    return date.toLocaleString('en-us', options);
}

function differenceInDays(start, end) {
    const resetTime = (date) => {
        date.setHours(0, 0, 0, 0);
    };

    const startDate = new Date(start);
    const endDate = new Date(end);

    resetTime(startDate);
    resetTime(endDate);

    const oneDay = 24 * 60 * 60 * 1000;
    const differenceMs = Math.abs(startDate.getTime() - endDate.getTime());
    const differenceDays = Math.round(differenceMs / oneDay);

    return differenceDays;
}

function getDateLabel(date) {
    const timeNow = new Date();
    const formmatedDate = new Date(formatDateInClientTimeZone(date));
    if (timeNow.getFullYear() !== formmatedDate.getFullYear()) {
        return formmatedDate.getDate() + " " + months[formmatedDate.getMonth()] + " " + formmatedDate.getFullYear();
    }
    const days = differenceInDays(formmatedDate, timeNow);

    if (days > 7) {
        return weekdays[formmatedDate.getDay()].substring(0, 3) + ", " + formmatedDate.getDate() + " " + months[formmatedDate.getMonth()];
    }

    if (days > 1) {
        return weekdays[formmatedDate.getDay()];
    }

    if (days === 1) {
        return "Yesterday";
    }
    return "Today";
}

function formatTime(date) {
    const formmatedDate = new Date(formatDateInClientTimeZone(date));
    const hours = formmatedDate.getHours();
    const minutes = formmatedDate.getMinutes();
    const amOrPm = hours >= 12 ? 'PM' : 'AM';
    const formattedHours = hours % 12 === 0 ? 12 : hours % 12;
    const formattedMinutes = minutes < 10 ? '0' + minutes : minutes;
    return `${formattedHours}:${formattedMinutes} ${amOrPm}`;
}


export { monthName, formatTime, getDateLabel, formatDateInClientTimeZone }