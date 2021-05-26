const char css[] PROGMEM = R"rawliteral(
     body,
      html {
        background-color: #e0e0e4;
      }
      body,
      p,
      input,
      select,
      textarea,
      button {
        font-family: "Montserrat", sans-serif;
        letter-spacing: -0.2px;
        font-size: 9px;
      }
      div,
      p {
        color: #babecc;
        text-shadow: 1px 1px 1px #fff;
      }
      form {
        padding: 30px;
        width: 320px;
        margin: 0 auto;
      }
      .segment {
        padding: 10px 0;
        text-align: center;
      }
      select,
      button,
      input {
        border: 0;
        outline: 0;
        font-size: 16px;
        border-radius: 320px;
        padding: 16px;
        background-color: #ebecf0;
      }
      input {
        margin-right: 8px;
        box-shadow: inset 2px 2px 5px #babecc, inset -5px -5px 10px #fff;
        width: 100%;
        box-sizing: border-box;
        transition: all 0.2s ease-in-out;
        appearance: none;
        -webkit-appearance: none;
      }
      input:focus {
        box-shadow: inset 1px 1px 2px #babecc, inset -1px -1px 2px #fff;
      }
      button {
        color: #61677c;
        font-weight: bold;
        box-shadow: -2px -2px 5px #fff, 2px 2px 5px #babecc;
        transition: all 0.2s ease-in-out;
        cursor: pointer;
        font-weight: 600;
      }
      .red:active,
      .unit:active {
        box-shadow: inset 1px 1px 2px #babecc, inset -1px -1px 2px #fff;
      }
      button .icon {
        margin-right: 8px;
      }
      button.unit {
        border-radius: 50%;
        line-height: 0;
        width: 52px;
        height: 52px;
        display: inline-flex;
        justify-content: center;
        align-items: center;
        margin: 0 8px;
        font-size: 19.2px;
      }
      button.unit .icon {
        margin-right: 0;
      }
      select,
      button.red {
        display: block;
        width: 100%;
        color: #ae1100;
      }
      .input-group {
        display: flex;
        align-items: center;
        justify-content: flex-start;
      }
      .input-group label {
        margin: 0;
        flex: 1;
      }
      select {
        width: 220px;
        -webkit-appearance: none;
        box-shadow: -2px -2px 5px #fff, 2px 2px 5px #babecc;
        text-align: center;
        font-weight: 900;
        cursor: pointer;
      }
      select:active {
        box-shadow: inset 1px 1px 2px #babecc, inset -1px -1px 2px #fff;
      }
)rawliteral";