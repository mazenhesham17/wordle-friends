import React from 'react'

export const Message = (props) => {
    return (
        <div style={{
            display: "flex", flexDirection: "column", textAlign: (props.sender ? "left" : "right")
            , width: "450px", background: (props.sender ? "cyan" : "green")
        }}>
            <h1>{props.message}</h1>
            <h2>{props.time}</h2>
        </div>
    )
}

export default Message;